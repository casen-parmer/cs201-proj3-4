# The mermaid package needs shell escape to run mmdc
$pdflatex = 'pdflatex -shell-escape %O %S';

# VS Code may not have Homebrew on its PATH, and mmdc needs both mmdc and node
$ENV{'PATH'} = "/opt/homebrew/bin:$ENV{'PATH'}";
