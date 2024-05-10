FROM python:3.9-slim
WORKDIR /app
ADD . /app
RUN pip install --no-cache-dir -r requirements.txt
CMD ["python", "app.py"]
