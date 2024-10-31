# Dockerfile
FROM ubuntu:20.04

# Set non-interactive frontend for apt-get
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt-get update && \
    apt-get install -y build-essential flex bison && \
    rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /usr/src/app

# Copy the entire project into the container
COPY . .

# Build the project using the Makefile
RUN make all

# Set the entry point to the built executable
CMD ["./calc"]
