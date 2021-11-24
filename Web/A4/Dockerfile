FROM python:3.9.7-buster

RUN apt-get update -y && \
    apt-get install -y python-pip python-dev

COPY ./app/requirements.txt /app/requirements.txt

WORKDIR /app


RUN pip install -r requirements.txt

COPY ./app /app

EXPOSE 9999

ENTRYPOINT [ "python" ]

CMD [ "app.py" ]