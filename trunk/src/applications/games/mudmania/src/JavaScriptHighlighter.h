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

#pragma once

#include <OEG/Common.h>

#include <QSyntaxHighlighter>
#include <QHash>
#include <QRegExp>
#include <QTextCharFormat>

class QTextDocument;

class JavaScriptHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT

  public:
    JavaScriptHighlighter(QTextDocument *parent = 0);

  protected:
    void highlightBlock(const QString &text);

  protected:
    struct HighlightingRule {
      QRegExp         pattern;
      QTextCharFormat format;
    };

    QVector<HighlightingRule> m_highlighting_rules;

    QRegExp         m_exp_comment_start;
    QRegExp         m_exp_comment_end;

    QTextCharFormat m_fmt_keyword;
    QTextCharFormat m_fmt_class;
    QTextCharFormat m_fmt_comment;
    QTextCharFormat m_fmt_quotation;
    QTextCharFormat m_fmt_function;
};

