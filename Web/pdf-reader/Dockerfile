FROM python:3.9.7-buster
COPY ./app/requirements.txt /
RUN pip3 install -r /requirements.txt

COPY ./app /app
WORKDIR /app
RUN pip install gunicorn
RUN apt-get update && apt-get install -y cron
RUN chmod +x ./gunicorn.sh
RUN mkdir /tmp/pdfcache
RUN crontab cleaner.cron
EXPOSE 4040
RUN echo "YetiCTF{1eV3l_ulTRa_H4ck3r}" > /flag.txt

ENTRYPOINT ["/bin/sh","/app/gunicorn.sh"]
