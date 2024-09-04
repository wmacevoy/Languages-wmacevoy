# .devcontainer/Dockerfile

# Use the base image for Java
FROM mcr.microsoft.com/devcontainers/java:1-21-bullseye

# Install required tools and dependencies
RUN apt-get update && apt-get install -y sudo git-crypt gnupg scala curl \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN  bash -c ". /usr/local/sdkman/bin/sdkman-init.sh; sdk install gradle"
