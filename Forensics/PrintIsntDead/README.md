__Category__: 
* Forensics

__Author__: 
* @RegularITCat

__Description__: 
Всё просто: ты, дамп трафика и конфиденциональная информация. Добро пожаловать!

__Flag__:
* YetiCTF{Fr3n4c0nn3ct10n}

__Files__:
* files/prntsndd.pcap

__Writeup__:
1. найти ipp траффик, найти пакет printjob
2. экспортировать из пакета printjob байты pdf-файла
3. в pdf-файле найти страницу с флагом YetiCTF{Fr3n4c0nn3ct10n} (4-ая по счету)