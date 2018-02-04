#include "../inc/scanner.h"

Scanner::Scanner(string context) : _context(context), _position(0), _prologUtils(PrologUtils::getInstance())
{
}

// Extract the next token from context.
pair<int, string> Scanner::nextToken()
{
    if (skipLeadingWhiteSpace() >= _context.length())
        return pair<int, string>(_prologUtils->EOS, "");
    else if (isEndChar())
        return extractChar();
    else if (islower(currentChar()))
        return extractAtom();
    else if (_prologUtils->isSpecialChar(currentChar()))
        return extractAtomSC();
    else if (currentChar() == '\'')
        return extractAtomSQ();
    else if (isdigit(currentChar()))
        return extractNumber();
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
    for (; isalnum(currentChar()) || isdigit(currentChar()) || currentChar() == '_'; _position++)
        ;
    return pair<int, string>(_prologUtils->ATOM, _context.substr(begin, _position - begin));
}

// Extract the atom which is composed of prolog special characters.
// Example: "#$&*+-./:<->?@^~\"
pair<int, string> Scanner::extractAtomSC()
{
    int begin = _position;
    for (; _prologUtils->isSpecialChar(currentChar()) && !isEndChar(); _position++)
        ;
    return pair<int, string>(_prologUtils->ATOM, _context.substr(begin, _position - begin));
}

// Extract the atom between single quote.
// Example: 'Do U Know Da Wai'.
pair<int, string> Scanner::extractAtomSQ()
{
    int begin = ++_position;
    _position = _context.find('\'', begin) + 1;
    return pair<int, string>(_prologUtils->ATOM, _context.substr(begin, _position - begin - 1));
}

// Extract the number.
// Example: 1, 0.1.
pair<int, string> Scanner::extractNumber()
{
    int begin = _position;
    bool hasPoint = false;
    for (; isNumberChar(hasPoint); _position++)
        ;
    return pair<int, string>(_prologUtils->NUMBER, _context.substr(begin, _position - begin));
}

// Extract the variable(upper case of leading character).
// Explosion, _member, De_ja_vu_01.
pair<int, string> Scanner::extractVariable()
{
    int begin = _position;
    for (; isdigit(currentChar()) || isalnum(currentChar()) || currentChar() == '_'; _position++)
        ;
    return pair<int, string>(_prologUtils->VAR, _context.substr(begin, _position - begin));
}

// Extract a character from now position.
pair<int, string> Scanner::extractChar()
{
    char c = _context[_position++];
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
    return _context[_position];
}

// Get next character.
char Scanner::nextChar()
{
    if (_position + 1 > _context.length())
        return '\0';
    return _context[_position + 1];
}

// Returns true if this character is a part of number.
bool Scanner::isNumberChar(bool &hasPoint)
{
    if (isdigit(currentChar()))
        return true;
    else if (!hasPoint && currentChar() == '.' && isdigit(nextChar()))
        return (hasPoint = true);
    return false;
}

// Returns true if '.' character is the last one.
bool Scanner::isEndChar()
{
    return (currentChar() == '.' && nextChar() == '\0');
}