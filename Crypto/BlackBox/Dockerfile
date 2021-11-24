FROM python:3.8.5
WORKDIR /code
COPY ./app/requrements.txt /code/requrements.txt
RUN pip install --no-cache-dir --upgrade -r /code/requrements.txt
COPY ./app/code /code/
EXPOSE 1117
CMD python task_BlackBox.py
