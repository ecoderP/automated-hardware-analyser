# System Log Analyzer

# system-diagnostic-and-log-processing-pipeline

This is an automated system-diagnostic-and-log-processing-pipeline.

run.sh

- Transfer process ownership to Python.
- Python is responsible for:
  - validating input
  - executing the C++ parser
  - analyzing the generated CSV
  - returning the final application exit status
