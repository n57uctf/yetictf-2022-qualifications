__Category__: 
* Forensics

__Author__: 
* @RegularITCat

__Description__: 
Этот парень был уверен в защищенности SSL...

__Flag__:
* YetiCTF{deAm1g0deCa7te1}

__Files__:
* files/sslett.pcap

__Writeup__:
1. из smtp пакетов достать base64
2. сохранить ssl ключи из base64 в файл и подключить файл для дешифровки ssl в wireshark
3. найти ссылку на github.com/jorgedeguzman
4. в репе mystuff из файла yeye.txt достать флаг в base64
5. декодировать base64 и получить флаг YetiCTF{deAm1g0deCa7te1}