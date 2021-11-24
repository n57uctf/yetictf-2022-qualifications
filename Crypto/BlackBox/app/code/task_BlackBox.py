import socket
from _thread import start_new_thread
import threading
import time

port = 1117 #Выбираем порт
ruls = [-4966, -5453, 7942, 5796, 3383] #флаг меняеться здесь!
flag = "YetiCTF{Ass3mbl3r_1s_the_b3st_Lang}"

def f(x):
	global ruls
	result = 1
	for i in ruls:
		result *= x - i
	return result

def check(ans):
	ruls.sort()
	if len(ruls) != len(ans):
		return False
	ans.sort()
	print(ruls, ans)
	for i in range(len(ruls)):
		print(ruls[i], ans[i])
		if ruls[i] != ans[i]:
			return False
	return True

def client(conn):
	global flag
	msg = '''
		Hi, let's play a math game. Your task is to find all the solutions of the unitary polynomial. 
		You can write me the number, after a while I will recalculate it to you and send the result.

		Send "e" to exit.

	>'''

	menu_msg = '''
	>s - Start game 
	>f - get Flag

	>'''
	
	while 1:
		conn.sendall(menu_msg.encode())
		inp = conn.recv(1024)
		if not inp:
			break
		#print(inp.decode()[:-1])
		try:
			res = inp.decode().strip('\n \t')
			if res.lower()[0] == 's': 
				conn.sendall(msg.encode())
				while True:
					inp = conn.recv(1024)
					if not inp or inp.decode().strip('\n \t')[0] == 'e':
						break
					res = int(inp.decode().strip('\n \t'))
					conn.sendall(" Please wait, a very complicated calculation is in progress...\n ".encode())
					time.sleep(20) 	# Защищаем от брутфорса. Конечно, можно сделать 100+ подключений и подобрать за минут 10
									# Но это должно все таки сдержать некоторых людей от этого желания.
					conn.sendall((str(f(res))+'\n >').encode())
			elif res.lower()[0] == 'f':
				conn.sendall('Write me your roots one by one. When you`rre done, write 0: \n>'.encode())
				inp = int(conn.recv(1024).decode().strip('\n \t'))
				ans = []
				while inp != 0:
					ans.append(inp)
					conn.sendall(" >".encode())
					inp = int(conn.recv(1024).decode().strip('\n \t'))
				if check(ans):
					conn.sendall("Wow, you figured it out. hold the flag: ".encode())
					conn.sendall(flag.encode())
					break
				else:
					conn.sendall(" Wrong answer\n".encode())
			else:
				conn.sendall(" I don`t understand you.\n".encode())
		except Exception as e:
			#print(e)
			conn.sendall(' Error. Try again.\n'.encode())
	conn.close()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', port))
s.listen(100)
print('start server')
while True:
	conn, addr = s.accept()
	print(addr)
	start_new_thread(client, (conn,))