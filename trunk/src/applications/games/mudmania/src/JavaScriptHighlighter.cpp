// $Id$
//
// Open eGovernment
// Copyright (C) 2005-2010 by Gerrit M. Albrecht
//
// This program is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

// http://doc.trolltech.com/4.1/qsyntaxhighlighter.html

#include <QFont>
#include <QRegExp>
#include <QStringList>
#include <QSyntaxHighlighter>
#include <QTextDocument>

#include "JavaScriptHighlighter.h"

JavaScriptHighlighter::JavaScriptHighlighter(QTextDocument *parent /*=0*/)
 : QSyntaxHighlighter(parent)
{
  HighlightingRule rule;

  // Formats.

  m_fmt_keyword.setFontWeight(QFont::Bold);
  m_fmt_keyword.setForeground(Qt::darkMagenta);

  // Keywords.

  QStringList keywords;

  keywords
    << "abstract"     << "boolean"   << "break"
    << "byte"         << "case"      << "catch"
    << "char"         << "class"     << "const"
    << "continue"     << "debugger"  << "default"
    << "delete"       << "do"        << "double"
    << "else"         << "enum"      << "export"
    << "extends"      << "false"     << "final"
    << "finally"      << "float"     << "for"
    << "function"     << "goto"      << "if"
    << "implements"   << "import"    << "in"
    << "instanceof"   << "int"       << "interface"
    << "long"         << "native"    << "new"
    << "null"         << "package"   << "private"
    << "protected"    << "public"    << "return"
    << "short"        << "static"    << "switch"
    << "synchronized" << "this"      << "throw"
    << "throws"       << "transient" << "true"
    << "try"          << "typeof"    << "var"
    << "void"         << "while"     << "with";

  foreach (QString keyword, keywords) {
    rule.pattern = QRegExp("\\b" + keyword + "\\b");
    rule.format  = m_fmt_keyword;

    m_highlighting_rules.append(rule);
  }

  m_fmt_class.setFontWeight(QFont::Bold);
  m_fmt_class.setForeground(Qt::darkMagenta);
  rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
  rule.format  = m_fmt_class;
  m_highlighting_rules.append(rule);

  m_fmt_comment.setForeground(Qt::red);
  rule.pattern = QRegExp("//[^\n]*");
  rule.format  = m_fmt_comment;
  m_highlighting_rules.append(rule);

  m_fmt_quotation.setForeground(Qt::darkGreen);
  rule.pattern = QRegExp("\".*\"");
  rule.format  = m_fmt_quotation;
  m_highlighting_rules.append(rule);

  rule.pattern = QRegExp("'.*'");
  rule.format  = m_fmt_quotation;
  m_highlighting_rules.append(rule);

  m_fmt_function.setFontItalic(true);
  m_fmt_function.setForeground(Qt::blue);
  rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
  rule.format  = m_fmt_function;
  m_highlighting_rules.append(rule);

  m_exp_comment_start = QRegExp("/\\*");
  m_exp_comment_end   = QRegExp("\\*/");
}

void JavaScriptHighlighter::highlightBlock(const QString &text)
{
  foreach (HighlightingRule rule, m_highlighting_rules) {
    QRegExp expression(rule.pattern);
    int index = text.indexOf(expression);

    while (index >= 0) {
      int length = expression.matchedLength();
      setFormat(index, length, rule.format);
      index = text.indexOf(expression, index + length);
    }
  }

  setCurrentBlockState(0);

  int startIndex = 0;
  if (previousBlockState() != 1)
    startIndex = text.indexOf(m_exp_comment_start);

  while (startIndex >= 0) {
    int endIndex = text.indexOf(m_exp_comment_end, startIndex);
    int commentLength;

    if (endIndex == -1) {
      setCurrentBlockState(1);
      commentLength = text.length() - startIndex;
    } else {
      commentLength = endIndex - startIndex + m_exp_comment_end.matchedLength();
    }

    setFormat(startIndex, commentLength, m_fmt_comment);

    startIndex = text.indexOf(m_exp_comment_start, startIndex + commentLength);
  }
}

