# Makefile

# Declare phony targets
.PHONY: all clean run reload

# Default target: reload the project to ensure it's up to date
all: reload

# Reload target: reload sbt to refresh build definitions and automatically compile if necessary
reload:
	sbt reload

# Clean target: clean the project
clean:
	sbt clean

# Run target: run the project
run: reload
	sbt run
