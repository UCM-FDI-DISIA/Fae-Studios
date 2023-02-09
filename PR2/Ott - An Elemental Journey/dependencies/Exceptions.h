#pragma once
#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

/// Clase base para las nuevas excepciones
class GameError : public logic_error {
public:
    GameError(const string& m) : logic_error(m) {};
};

/// Excepciones que tengan que ver con SDL
class SDLError : public GameError {
public:
    SDLError(const string& m) : GameError(m) {};
};

/// Excepción si el archivo de texto no se ha encontrado
class FileNotFoundError : public GameError {
protected:
    string filename;
public:
    FileNotFoundError(const string& m, const string& file) :
            GameError(m + "File \"" + file + "\" not found"), filename(file) {};
};

/// Excepción si el formato del archivo de texto es incorrecto
class FileFormatError : public GameError {
protected:
    int line;
    string filename;
public:
    FileFormatError(const string& m, int l, const string& file) :
            GameError(m + "Incorrect format in file \"" + file + "\" in line " + to_string(l)), line(l),
            filename(file) {};
};

