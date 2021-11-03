package main

import (
	"encoding/binary"
	"fmt"
	"io"
	"log"
	"net"
	"strings"
	"time"
)

const (
	CONN_HOST = "0.0.0.0"
	CONN_PORT = "502"
	FLAG      = "YetiCTF{c00l3r_7h4n_57uxn37_br0}"
)

// Exception codes.
type Exception uint8

var (
	// Success operation successful.
	Success Exception
	// IllegalFunction function code received in the query is not recognized or allowed by slave.
	IllegalFunction Exception = 1
	// IllegalDataAddress data address of some or all the required entities are not allowed or do not exist in slave.
	IllegalDataAddress Exception = 2
	// IllegalDataValue value is not accepted by slave.
	IllegalDataValue Exception = 3
	// SlaveDeviceFailure Unrecoverable error occurred while slave was attempting to perform requested action.
	SlaveDeviceFailure Exception = 4
	// AcknowledgeSlave has accepted request and is processing it, but a long duration of time is required. This response is returned to prevent a timeout error from occurring in the master. Master can next issue a Poll Program Complete message to determine whether processing is completed.
	AcknowledgeSlave Exception = 5
	// SlaveDeviceBusy is engaged in processing a long-duration command. Master should retry later.
	SlaveDeviceBusy Exception = 6
	// NegativeAcknowledge Slave cannot perform the programming functions. Master should request diagnostic or error information from slave.
	NegativeAcknowledge Exception = 7
	// MemoryParityError Slave detected a parity error in memory. Master can retry the request, but service may be required on the slave device.
	MemoryParityError Exception = 8
	// GatewayPathUnavailable Specialized for Modbus gateways. Indicates a misconfigured gateway.
	GatewayPathUnavailable Exception = 10
	// GatewayTargetDeviceFailedtoRespond Specialized for Modbus gateways. Sent when slave fails to respond.
	GatewayTargetDeviceFailedtoRespond Exception = 11
)

func (e Exception) Error() string {
	return fmt.Sprintf("%d", e)
}

func (e Exception) String() string {
	var str string
	switch e {
	case Success:
		str = fmt.Sprintf("Success")
	case IllegalFunction:
		str = fmt.Sprintf("IllegalFunction")
	case IllegalDataAddress:
		str = fmt.Sprintf("IllegalDataAddress")
	case IllegalDataValue:
		str = fmt.Sprintf("IllegalDataValue")
	case SlaveDeviceFailure:
		str = fmt.Sprintf("SlaveDeviceFailure")
	case AcknowledgeSlave:
		str = fmt.Sprintf("AcknowledgeSlave")
	case SlaveDeviceBusy:
		str = fmt.Sprintf("SlaveDeviceBusy")
	case NegativeAcknowledge:
		str = fmt.Sprintf("NegativeAcknowledge")
	case MemoryParityError:
		str = fmt.Sprintf("MemoryParityError")
	case GatewayPathUnavailable:
		str = fmt.Sprintf("GatewayPathUnavailable")
	case GatewayTargetDeviceFailedtoRespond:
		str = fmt.Sprintf("GatewayTargetDeviceFailedtoRespond")
	default:
		str = fmt.Sprintf("unknown")
	}
	return str
}

// Framer is the interface that wraps Modbus frames.
type Framer interface {
	Bytes() []byte
	Copy() Framer
	GetData() []byte
	GetFunction() uint8
	SetException(exception *Exception)
	SetData(data []byte)
}

// GetException retunrns the Modbus exception or Success (indicating not exception).
func GetException(frame Framer) (exception Exception) {
	function := frame.GetFunction()
	if (function & 0x80) != 0 {
		exception = Exception(frame.GetData()[0])
	}
	return exception
}

func registerAddressAndNumber(frame Framer) (register int, numRegs int, endRegister int) {
	data := frame.GetData()
	register = int(binary.BigEndian.Uint16(data[0:2]))
	numRegs = int(binary.BigEndian.Uint16(data[2:4]))
	endRegister = register + numRegs
	return register, numRegs, endRegister
}

func registerAddressAndValue(frame Framer) (int, uint16) {
	data := frame.GetData()
	register := int(binary.BigEndian.Uint16(data[0:2]))
	value := binary.BigEndian.Uint16(data[2:4])
	return register, value
}

// SetDataWithRegisterAndNumber sets the RTUFrame Data byte field to hold a register and number of registers
func SetDataWithRegisterAndNumber(frame Framer, register uint16, number uint16) {
	data := make([]byte, 4)
	binary.BigEndian.PutUint16(data[0:2], register)
	binary.BigEndian.PutUint16(data[2:4], number)
	frame.SetData(data)
}

// SetDataWithRegisterAndNumberAndValues sets the TCPFrame Data byte field to hold a register and number of registers and values
func SetDataWithRegisterAndNumberAndValues(frame Framer, register uint16, number uint16, values []uint16) {
	data := make([]byte, 5+len(values)*2)
	binary.BigEndian.PutUint16(data[0:2], register)
	binary.BigEndian.PutUint16(data[2:4], number)
	data[4] = uint8(len(values) * 2)
	copy(data[5:], Uint16ToBytes(values))
	frame.SetData(data)
}

// SetDataWithRegisterAndNumberAndBytes sets the TCPFrame Data byte field to hold a register and number of registers and coil bytes
func SetDataWithRegisterAndNumberAndBytes(frame Framer, register uint16, number uint16, bytes []byte) {
	data := make([]byte, 5+len(bytes))
	binary.BigEndian.PutUint16(data[0:2], register)
	binary.BigEndian.PutUint16(data[2:4], number)
	data[4] = byte(len(bytes))
	copy(data[5:], bytes)
	frame.SetData(data)
}

// TCPFrame is the Modbus TCP frame.
type TCPFrame struct {
	TransactionIdentifier uint16
	ProtocolIdentifier    uint16
	Length                uint16
	Device                uint8
	Function              uint8
	Data                  []byte
}

// NewTCPFrame converts a packet to a Modbus TCP frame.
func NewTCPFrame(packet []byte) (*TCPFrame, error) {
	// Check if the packet is too short.
	if len(packet) < 9 {
		return nil, fmt.Errorf("TCP Frame error: packet less than 9 bytes")
	}

	frame := &TCPFrame{
		TransactionIdentifier: binary.BigEndian.Uint16(packet[0:2]),
		ProtocolIdentifier:    binary.BigEndian.Uint16(packet[2:4]),
		Length:                binary.BigEndian.Uint16(packet[4:6]),
		Device:                uint8(packet[6]),
		Function:              uint8(packet[7]),
		Data:                  packet[8:],
	}

	// Check expected vs actual packet length.
	if int(frame.Length) != len(frame.Data)+2 {
		return nil, fmt.Errorf("specified packet length does not match actual packet length")
	}

	return frame, nil
}

// Copy the TCPFrame.
func (frame *TCPFrame) Copy() Framer {
	copy := *frame
	return &copy
}

// Bytes returns the Modbus byte stream based on the TCPFrame fields
func (frame *TCPFrame) Bytes() []byte {
	bytes := make([]byte, 8)

	binary.BigEndian.PutUint16(bytes[0:2], frame.TransactionIdentifier)
	binary.BigEndian.PutUint16(bytes[2:4], frame.ProtocolIdentifier)
	binary.BigEndian.PutUint16(bytes[4:6], uint16(2+len(frame.Data)))
	bytes[6] = frame.Device
	bytes[7] = frame.Function
	bytes = append(bytes, frame.Data...)

	return bytes
}

// GetFunction returns the Modbus function code.
func (frame *TCPFrame) GetFunction() uint8 {
	return frame.Function
}

// GetData returns the TCPFrame Data byte field.
func (frame *TCPFrame) GetData() []byte {
	return frame.Data
}

// SetData sets the TCPFrame Data byte field and updates the frame length
// accordingly.
func (frame *TCPFrame) SetData(data []byte) {
	frame.Data = data
	frame.setLength()
}

// SetException sets the Modbus exception code in the frame.
func (frame *TCPFrame) SetException(exception *Exception) {
	frame.Function = frame.Function | 0x80
	frame.Data = []byte{byte(*exception)}
	frame.setLength()
}

func (frame *TCPFrame) setLength() {
	frame.Length = uint16(len(frame.Data) + 2)
}

func (s *Server) accept(listen net.Listener) error {
	for {
		conn, err := listen.Accept()
		if err != nil {
			if strings.Contains(err.Error(), "use of closed network connection") {
				return nil
			}
			log.Printf("Unable to accept connections: %#v\n", err)
			return err
		}

		go func(conn net.Conn) {
			defer conn.Close()

			for {
				packet := make([]byte, 512)
				bytesRead, err := conn.Read(packet)
				if err != nil {
					if err != io.EOF {
						log.Printf("read error %v\n", err)
					}
					return
				}
				// Set the length of the packet to the number of read bytes.
				packet = packet[:bytesRead]

				frame, err := NewTCPFrame(packet)
				if err != nil {
					log.Printf("bad packet error %v\n", err)
					return
				}

				request := &Request{conn, frame}

				s.requestChan <- request
			}
		}(conn)
	}
}

// ListenTCP starts the Modbus server listening on "address:port".
func (s *Server) ListenTCP(addressPort string) (err error) {
	listen, err := net.Listen("tcp", addressPort)
	if err != nil {
		log.Printf("Failed to Listen: %v\n", err)
		return err
	}
	s.listeners = append(s.listeners, listen)
	go s.accept(listen)
	return err
}

// ReadCoils function 1, reads coils from internal memory.
func ReadCoils(s *Server, frame Framer) ([]byte, *Exception) {
	register, numRegs, endRegister := registerAddressAndNumber(frame)
	if endRegister > 65535 {
		return []byte{}, &IllegalDataAddress
	}
	dataSize := numRegs / 8
	if (numRegs % 8) != 0 {
		dataSize++
	}
	data := make([]byte, 1+dataSize)
	data[0] = byte(dataSize)
	for i, value := range s.Coils[register:endRegister] {
		if value != 0 {
			shift := uint(i) % 8
			data[1+i/8] |= byte(1 << shift)
		}
	}
	return data, &Success
}

// ReadDiscreteInputs function 2, reads discrete inputs from internal memory.
func ReadDiscreteInputs(s *Server, frame Framer) ([]byte, *Exception) {
	register, numRegs, endRegister := registerAddressAndNumber(frame)
	if endRegister > 65535 {
		return []byte{}, &IllegalDataAddress
	}
	dataSize := numRegs / 8
	if (numRegs % 8) != 0 {
		dataSize++
	}
	data := make([]byte, 1+dataSize)
	data[0] = byte(dataSize)
	for i, value := range s.DiscreteInputs[register:endRegister] {
		if value != 0 {
			shift := uint(i) % 8
			data[1+i/8] |= byte(1 << shift)
		}
	}
	return data, &Success
}

// ReadHoldingRegisters function 3, reads holding registers from internal memory.
func ReadHoldingRegisters(s *Server, frame Framer) ([]byte, *Exception) {
	register, numRegs, endRegister := registerAddressAndNumber(frame)
	if endRegister > 65536 {
		return []byte{}, &IllegalDataAddress
	}
	return append([]byte{byte(numRegs * 2)}, Uint16ToBytes(s.HoldingRegisters[register:endRegister])...), &Success
}

// ReadInputRegisters function 4, reads input registers from internal memory.
func ReadInputRegisters(s *Server, frame Framer) ([]byte, *Exception) {
	register, numRegs, endRegister := registerAddressAndNumber(frame)
	if endRegister > 65536 {
		return []byte{}, &IllegalDataAddress
	}
	return append([]byte{byte(numRegs * 2)}, Uint16ToBytes(s.InputRegisters[register:endRegister])...), &Success
}

// BytesToUint16 converts a big endian array of bytes to an array of unit16s
func BytesToUint16(bytes []byte) []uint16 {
	values := make([]uint16, len(bytes)/2)

	for i := range values {
		values[i] = binary.BigEndian.Uint16(bytes[i*2 : (i+1)*2])
	}
	return values
}

// Uint16ToBytes converts an array of uint16s to a big endian array of bytes
func Uint16ToBytes(values []uint16) []byte {
	bytes := make([]byte, len(values)*2)

	for i, value := range values {
		binary.BigEndian.PutUint16(bytes[i*2:(i+1)*2], value)
	}
	return bytes
}

func bitAtPosition(value uint8, pos uint) uint8 {
	return (value >> pos) & 0x01
}

// Server is a Modbus slave with allocated memory for discrete inputs, coils, etc.
type Server struct {
	// Debug enables more verbose messaging.
	Debug            bool
	listeners        []net.Listener
	requestChan      chan *Request
	function         [256](func(*Server, Framer) ([]byte, *Exception))
	DiscreteInputs   []byte
	Coils            []byte
	HoldingRegisters []uint16
	InputRegisters   []uint16
}

// Request contains the connection and Modbus frame.
type Request struct {
	conn  io.ReadWriteCloser
	frame Framer
}

// NewServer creates a new Modbus server (slave).
func NewServer() *Server {
	s := &Server{}

	// Allocate Modbus memory maps.
	s.DiscreteInputs = make([]byte, 65536)
	s.Coils = make([]byte, 65536)
	s.HoldingRegisters = make([]uint16, 65536)
	for i, v := range FLAG {
		s.HoldingRegisters[i] = uint16(v)
	}
	s.InputRegisters = make([]uint16, 65536)

	// Add default functions.
	s.function[1] = ReadCoils
	s.function[2] = ReadDiscreteInputs
	s.function[3] = ReadHoldingRegisters
	s.function[4] = ReadInputRegisters

	s.requestChan = make(chan *Request)
	go s.handler()

	return s
}

// RegisterFunctionHandler override the default behavior for a given Modbus function.
func (s *Server) RegisterFunctionHandler(funcCode uint8, function func(*Server, Framer) ([]byte, *Exception)) {
	s.function[funcCode] = function
}

func (s *Server) handle(request *Request) Framer {
	var exception *Exception
	var data []byte

	response := request.frame.Copy()

	function := request.frame.GetFunction()
	if s.function[function] != nil {
		data, exception = s.function[function](s, request.frame)
		response.SetData(data)
	} else {
		exception = &IllegalFunction
	}

	if exception != &Success {
		response.SetException(exception)
	}

	return response
}

// All requests are handled synchronously to prevent modbus memory corruption.
func (s *Server) handler() {
	for {
		request := <-s.requestChan
		response := s.handle(request)
		request.conn.Write(response.Bytes())
	}
}

// Close stops listening to TCP/IP ports and closes serial ports.
func (s *Server) Close() {
	for _, listen := range s.listeners {
		listen.Close()
	}
}

func main() {
	serv := NewServer()
	err := serv.ListenTCP(CONN_HOST + ":" + CONN_PORT)
	if err != nil {
		log.Printf("%v\n", err)
	}
	defer serv.Close()

	// Wait forever
	for {
		time.Sleep(1 * time.Second)
	}
}
