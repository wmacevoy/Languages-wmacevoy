# .devcontainer/Dockerfile

# Use the base image for Java
FROM mcr.microsoft.com/devcontainers/java:1-21-bullseye

# Install required tools and dependencies
# Install required tools and dependencies
RUN apt-get update && apt-get install -y sudo git-crypt gnupg scala curl \
    && curl -sL https://deb.nodesource.com/setup_14.x | sudo -E bash - \
    && echo "deb https://scala.jfrog.io/artifactory/debian all main" | sudo tee /etc/apt/sources.list.d/sbt.list \
    && curl -sL "https://keyserver.ubuntu.com/pks/lookup?op=get&search=0x99E82A75642AC823" | sudo apt-key add - \
    && apt-get update && apt-get install -y sbt \
    && apt-get clean && rm -rf /var/lib/apt/lists/*
RUN  bash -c ". /usr/local/sdkman/bin/sdkman-init.sh; sdk install gradle"
