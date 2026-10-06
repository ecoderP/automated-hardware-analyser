```bash
#!/bin/bash

# ==============================================================================
# System Log Analyzer - Build & Launch Script
#
# This script:
#   - Verifies required tools are available
#   - Compiles the C++ log parser
#   - Hands application control to the Python controller
#
# Application orchestration and analysis are handled by controller.py.
# ===================================================================

set -euo pipefail


# Configuration
# ================================================

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PARSER_SOURCE="$SCRIPT_DIR/parser.cpp"
PARSER_BINARY="$SCRIPT_DIR/parser"
PYTHON_PIPELINE="$SCRIPT_DIR/controller.py"


# Helper Functions
# ===================================================

check_command() {
    local command_name="$1"

    if ! command -v "$command_name" >/dev/null 2>&1; then
        echo "[Bash ERROR] Required command '$command_name' is not installed."
        exit 1
    fi
}


# Environment Validation
# =================================================

echo "============================================================"
echo "        SYSTEM LOG ANALYZER - BUILD & LAUNCH"
echo "============================================================"

echo "[Bash] Checking required tools..."

check_command "g++"
check_command "python3"

echo "[Bash] Required tools are available."


# Source Validation
# ==============================================================================

if [[ ! -f "$PARSER_SOURCE" ]]; then
    echo "[Bash ERROR] C++ source file not found: $PARSER_SOURCE"
    exit 1
fi

if [[ ! -f "$PYTHON_PIPELINE" ]]; then
    echo "[Bash ERROR] Python pipeline not found: $PYTHON_PIPELINE"
    exit 1
fi


# C++ code Compilation
# ==============================================================================

echo "[Bash] Compiling C++ log parser..."

g++ \
    -std=c++17 \
    -Wall \
    -Wextra \
    -Wpedantic \
    -O2 \
    -o "$PARSER_BINARY" \
    "$PARSER_SOURCE"

echo "[Bash] C++ compilation successful."
echo "[Bash] Parser binary: $PARSER_BINARY"


# Application Handoff
# ======================================

echo "----------------------------------------------------"
echo "[Bash] Starting Python application pipeline..."
echo "-----------------------------------------------------"

exec python3 "$PYTHON_PIPELINE"
```