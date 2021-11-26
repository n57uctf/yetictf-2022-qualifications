__Category__: 
* Forensics

__Author__: 
* @slyshay6

__Description__: 
Киберполиция взяла подозреваемого в ботнетоводстве, но он вайпнул все до их прибытия. У наших инженеров, которые вели за ним киберслежку, остался дамп трафика с его сети. Они утверждают, что угроза миновала, хотя я сомневаюсь в их словах.

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
