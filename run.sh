#!/bin/bash

# Nombre del ejecutable
EXEC=programa

# Compilación automática
echo "Buscando archivos .cpp..."

# Buscar todos los archivos .cpp recursivamente
CPP_FILES=$(find . -name "*.cpp" -type f)

if [ -z "$CPP_FILES" ]; then
    echo "❌ No se encontraron archivos .cpp"
    exit 1
fi

echo "Archivos encontrados:"
echo "$CPP_FILES" | sed 's/^/  - /'

echo ""
echo "Compilando..."

# Compilar con includes automáticos
# Buscar directorios que contengan archivos .h o .hpp
INCLUDE_DIRS=$(find . -name "*.h" -o -name "*.hpp" | xargs dirname | sort -u | sed 's/^/-I/')

clang++ -std=c++17 -Wall -Wextra $INCLUDE_DIRS $CPP_FILES -o $EXEC

# Verifica que la compilación fue exitosa
if [ $? -eq 0 ]; then
    echo "✅ Compilación exitosa. Ejecutando..."
    echo "----------------------------------------"
    ./$EXEC
else
    echo "❌ Error en la compilación."
    exit 1
fi