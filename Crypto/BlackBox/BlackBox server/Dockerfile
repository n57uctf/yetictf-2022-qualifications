FROM python:3.8.5
WORKDIR /code
COPY ./requrements.txt /code/requrements.txt
RUN pip install --no-cache-dir --upgrade -r /code/requrements.txt
COPY ./crypto /code/project
CMD python task_BlackBox.py
