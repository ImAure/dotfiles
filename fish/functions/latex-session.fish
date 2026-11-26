function latex-session --wraps='v . & latexmk -pvc & z main.pdf' --description 'alias latex-session=v . & latexmk -pvc & z main.pdf'
    v . & latexmk -pvc & z main.pdf $argv
end
