FROM python:3.9-slim

# Set direktori kerja
WORKDIR /app

# Install dependensi sistem dengan nama paket yang benar
RUN apt-get update && apt-get install -y \
    libgl1 \
    libglib2.0-0 \
    && rm -rf /var/lib/apt/lists/*

# Salin file requirements
COPY requirements.txt /app/

# Instal dependensi Python
RUN pip install --no-cache-dir -r requirements.txt

# Salin sisa kode aplikasi
COPY . /app/

# (Opsional) Mengubah kepemilikan
RUN chown -R 1000:1000 /app

# Ekspos port
EXPOSE 5000

# Perintah untuk menjalankan aplikasi
CMD ["flask", "run", "--host=0.0.0.0", "--port=5000"]
