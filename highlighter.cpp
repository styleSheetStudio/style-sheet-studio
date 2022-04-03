#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
     : QSyntaxHighlighter(parent)
 {
     HighlightingRule rule;
     QColor blue;
     blue.setRgb(0,102,153);
     keywordFormat.setForeground(blue);
   //  keywordFormat.setFontWeight(QFont::Bold);
     QStringList keywordPatterns;
     keywordPatterns << "\\bfont\\b" << "\\btext-align\\b" << "\\bcolor\\b"
                     << "\\bbackground-color\\b"  << "\\bbackground-image\\b"  << "\\background-repeat\\b"
                     << "\\bbackground-position\\b"  << "\\bborder-radius\\b"     << "\\bborder-width\\b"  << "\\bborder-color\\b"
                          << "\\bborder-style\\b" << "\\bpadding\\b"<<"\\bbackground-repeat\\b";
     foreach (const QString &pattern, keywordPatterns) {
         rule.pattern = QRegExp(pattern);
         rule.format = keywordFormat;
         highlightingRules.append(rule);
     }




     QColor green;
     green.setRgb(0,153,0);
 //    classFormat.setFontWeight(QFont::Bold);
     classFormat.setForeground(green);
     rule.pattern = QRegExp("#[0-9A-Fa-f]{6}|[0-9]+(pt)|[0-9]+(px)|[0-9]+|(bottom)|(centre)|(bottom-right)|(bottom-left)|(top)|(centre-left)|(centre-right)|(no-repeat)|(url)|Q[a-zA-Z\:]+");
     rule.format = classFormat;
     highlightingRules.append(rule);

     singleLineCommentFormat.setForeground(Qt::red);
     rule.pattern = QRegExp("//[^\n]*");
     rule.format = singleLineCommentFormat;
     highlightingRules.append(rule);

     multiLineCommentFormat.setForeground(Qt::red);

     quotationFormat.setForeground(Qt::darkGreen);
     rule.pattern = QRegExp("\".*\"");
     rule.format = quotationFormat;
     highlightingRules.append(rule);

    // functionFormat.setFontItalic(true);
     functionFormat.setForeground(Qt::blue);
     rule.pattern = QRegExp("(')[a-zA-Z\-]+(')");
     rule.format = functionFormat;
     highlightingRules.append(rule);

     commentStartExpression = QRegExp("/\\*");
     commentEndExpression = QRegExp("\\*/");
 }

 void Highlighter::highlightBlock(const QString &text)
 {
     foreach (const HighlightingRule &rule, highlightingRules) {
         QRegExp expression(rule.pattern);
         int index = expression.indexIn(text);
         while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, rule.format);
             index = expression.indexIn(text, index + length);
         }
     }
     setCurrentBlockState(0);

     int startIndex = 0;
     if (previousBlockState() != 1)
         startIndex = commentStartExpression.indexIn(text);

     while (startIndex >= 0) {
         int endIndex = commentEndExpression.indexIn(text, startIndex);
         int commentLength;
         if (endIndex == -1) {
             setCurrentBlockState(1);
             commentLength = text.length() - startIndex;
         } else {
             commentLength = endIndex - startIndex
                             + commentEndExpression.matchedLength();
         }
         setFormat(startIndex, commentLength, multiLineCommentFormat);
         startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
     }
 }
