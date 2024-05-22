\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{iiuwb}[2011/11/26 Institute of Informatics of UwB LaTeX class]
\DeclareOption*{% wszystkie opcje
\PassOptionsToClass{\CurrentOption}{report}}
\ProcessOptions
\LoadClass[12pt,a4paper,twoside]{report}
\RequirePackage[T1]{fontenc}
\RequirePackage[utf8]{inputenc}
\RequirePackage{array,graphicx,ifthen,float}

%Komendy, które muszą być nadpisane przez autora
\DeclareRobustCommand{\imiona}{Imię}
\DeclareRobustCommand{\nazwiska}{Nazwisko}

\DeclareRobustCommand{\stopienpromotora}{dr}
\DeclareRobustCommand{\imionapromotora}{Promotor}
\DeclareRobustCommand{\nazwiskapromotora}{Promotor}
\DeclareRobustCommand{\profuwb}{TAK}

\DeclareRobustCommand{\stopienasystenta}{dr}
\DeclareRobustCommand{\imionaasystenta}{Asystent}
\DeclareRobustCommand{\nazwiskaasystenta}{Asystent}

\DeclareRobustCommand{\rok}{2012}
\DeclareRobustCommand{\tytul}{Tytuł}
\DeclareRobustCommand{\zaklad}{Zakład}
\DeclareRobustCommand{\album}{00000}
\DeclareRobustCommand{\rokakademicki}{2011/2012}
\DeclareRobustCommand{\kierunek}{Informatyka}
\DeclareRobustCommand{\sciezka}{Informatyka teoretyczna}
\DeclareRobustCommand{\rodzaj}{Stacjonarne}
\DeclareRobustCommand{\poziom}{I stopnia}

\DeclareRobustCommand{\stronatytulowa}{%
\begin{titlepage}\Large
\begin{center}
UNIWERSYTET W BIAŁYMSTOKU\\
WYDZIAŁ INFORMATYKI
\end{center}
\vfill
\begin{center}
{\large \imiona{} \MakeUppercase{\nazwiska}}\\
\end{center}
\vfill
\begin{center}
{\LARGE \textbf{\tytul}}
\end{center}
\vfill
\begin{flushright}
\begin{tabular}{r}

Promotor:\\
\stopienpromotora\ \imionapromotora{} \MakeUppercase{\nazwiskapromotora}\ifthenelse{\equal{\profuwb}{TAK}}{, prof. UwB}{}
\\

\ifthenelse{\NOT{\equal{\nazwiskaasystenta}{}}}{
Asystent:\\
\stopienasystenta\ \imionaasystenta{} \MakeUppercase{\nazwiskaasystenta}\\
}{}
\end{tabular}
\end{flushright}
\vfill
\begin{center}
BIAŁYSTOK \rok
\end{center}
\end{titlepage}
}


\AtBeginDocument{%
\renewcommand{\baselinestretch}{1.3}
\stronatytulowa\newpage
\setcounter{page}{2}
\cleardoublepage
}

%POZIOM

\setlength{\hoffset}{-1in}
\setlength{\oddsidemargin}{35mm}
\setlength{\evensidemargin}{25mm}
\setlength{\textwidth}{150mm}
\setlength{\marginparsep}{0mm}
\setlength{\marginparwidth}{0mm}

%PION

\setlength{\voffset}{-1in}
\setlength{\topmargin}{25mm}
\setlength{\headheight}{0mm}
\setlength{\headsep}{0mm}
\setlength{\textheight}{247mm}
\setlength{\footskip}{15mm}

\endinput
