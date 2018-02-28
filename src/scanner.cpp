#include "../inc/scanner.h"

Scanner::Scanner(string content) : _content(content), _position(0), _prologUtils(PrologUtils::getInstance())
{
}

// Extract the next token from content.
pair<int, string> Scanner::nextToken()
{
    if (skipLeadingWhiteSpace() >= _content.length())
        return pair<int, string>(_prologUtils->EOS, "");
    else if (isEndChar())
        return extractChar();
    else if (isdigit(currentChar()) || (currentChar() == '-' && isdigit(nextChar())))
        return extractNumber();
    else if (islower(currentChar()))
        return extractAtom();
    else if (_prologUtils->isSpecialChar(currentChar()))
        return extractAtomSC();
    else if (currentChar() == '\'')
        return extractAtomSQ();
    else if (isupper(currentChar()) || currentChar() == '_')
        return extractVariable();
    else
        return extractChar();
}

// Skip the white space before character.
int Scanner::skipLeadingWhiteSpace()
{
    for (; currentChar() == ' ' || currentChar() == '\t'; _position++)
        ;
    return _position;
}

// Extract the normal atom(lower case of leading character).
// Example: a, tom, c8763, dAWai
pair<int, string> Scanner::extractAtom()
{
    int begin = _position;
    for (; isCharacter(); _position++)
        ;
    return pair<int, string>(_prologUtils->ATOM, _content.substr(begin, _position - begin));
}

// Extract the atom which is composed of prolog special characters.
// Example: "#$&*+-./:<->?@^~\"
pair<int, string> Scanner::extractAtomSC()
{
    int begin = _position;
    for (; _prologUtils->isSpecialChar(currentChar()) && !isEndChar(); _position++)
        ;
    return pair<int, string>(_prologUtils->ATOM, _content.substr(begin, _position - begin));
}

// Extract the atom between single quote.
// Example: 'Do U Know Da Wai'.
pair<int, string> Scanner::extractAtomSQ()
{
    int begin = _position;
    _position = _content.find('\'', begin + 1) + 1;
    return pair<int, string>(_prologUtils->ATOM, _content.substr(begin, _position - begin));
}

// Extract the number.
// Example: 1, 0.1, -0.1
pair<int, string> Scanner::extractNumber()
{
    int begin = _position;
    bool hasPoint = false;
    if (currentChar() == '-')
        _position++;
    for (; isNumber(hasPoint); _position++)
        ;
    return pair<int, string>(_prologUtils->NUMBER, _content.substr(begin, _position - begin));
}

// Extract the variable(upper case of leading character).
// Explosion, _member, De_ja_vu_01.
pair<int, string> Scanner::extractVariable()
{
    int begin = _position;
    for (; isCharacter(); _position++)
        ;
    return pair<int, string>(_prologUtils->VAR, _content.substr(begin, _position - begin));
}

// Extract a character from now position.
pair<int, string> Scanner::extractChar()
{
    char c = _content[_position++];
    return pair<int, string>(c, string(1, c));
}

// Get now position.
int Scanner::position()
{
    return _position;
}

// Get current character.
char Scanner::currentChar()
{
    return _content[_position];
}

// Get next character.
char Scanner::nextChar()
{
    if (_position + 1 > _content.length())
        return '\0';
    return _content[_position + 1];
}

// Returns true if current character is a port of atom or variable
bool Scanner::isCharacter()
{
    char c = currentChar();
    return (isdigit(c) || isalnum(c) || c == '_');
}

// Returns true if current character is a port of number
bool Scanner::isNumber(bool &hasPoint)
{
    char c = currentChar();
    if (isdigit(c))
        return true;
    else if (!hasPoint && c == '.' && isdigit(nextChar()))
        return (hasPoint = true);
    else
        return false;
}

// Returns true if '.' character is the last one.
bool Scanner::isEndChar()
{
    return (currentChar() == '.' && nextChar() == '\0');
}