FROM python:3.9-slim

# Set working directory
WORKDIR /app

# No system dependencies needed for now (MQTT only)

# Copy requirements file
COPY requirements.txt /app/

# Install Python dependencies
RUN pip install --no-cache-dir -r requirements.txt

# Copy the rest of the application code
COPY . /app/

# Change ownership of the app directory to allow editing
RUN chown -R 1000:1000 /app

# Expose port
EXPOSE 5000

# Command to run the application
CMD ["flask", "run", "--host=0.0.0.0"]
