package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"math"
	"os"
	"runtime/pprof"
	"strconv"
	"strings"
)

var cpuprofile = flag.String("cpuprofile", "", "write cpu profile to file")

type Doenca struct {
	codigo             string
	genes              []string
	probabilidade      int
	printProbabilidade string
}

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func achaPadrao(gene, texto string, subcadeiaMin int) int {
	tamGene := len(gene)
	tamTexto := len(texto)
	indexGene := 0
	indexTexto := 0
	subcadeiaAux := 0
	sumSubcadeiaIgual := 0
	limiar := (tamGene * 9)
	for (tamTexto - indexTexto) >= (tamGene - indexGene) {
		if gene[indexGene] == texto[indexTexto] {
			indexGene++
			indexTexto++
			sumSubcadeiaIgual++
		}
		if (sumSubcadeiaIgual)*10 >= limiar {
			if (sumSubcadeiaIgual == subcadeiaAux) || (sumSubcadeiaIgual-subcadeiaAux >= subcadeiaMin) {
				return 1
			}
		}
		if indexTexto < tamTexto && gene[indexGene] != texto[indexTexto] {
			if sumSubcadeiaIgual-subcadeiaAux >= subcadeiaMin {
				if tamGene-indexGene < subcadeiaMin {
					return 0
				}
				subcadeiaAux = sumSubcadeiaIgual
				indexTexto++
			} else {
				if indexGene > subcadeiaAux {
					indexGene = subcadeiaAux
					indexTexto -= sumSubcadeiaIgual - subcadeiaAux - 1
					sumSubcadeiaIgual = subcadeiaAux
				} else {
					sumSubcadeiaIgual = subcadeiaAux
					indexTexto++
				}
			}
		}
	}
	return 0
}

func achaCompat(doencas []Doenca, numDoencas int, subcadeia int, texto string) [][]Doenca {
	acc := make([][]Doenca, 101)
	for i := 0; i < numDoencas; i++ {
		doencas[i].probabilidade = 0
		qtdGenes := len(doencas[i].genes)
		for j := 0; j < qtdGenes; j++ {
			doencas[i].probabilidade += achaPadrao(doencas[i].genes[j], texto, subcadeia)
		}
		doencas[i].probabilidade = int(math.Round(float64(doencas[i].probabilidade*100) / float64(qtdGenes)))
		acc[doencas[i].probabilidade] = append(acc[doencas[i].probabilidade], doencas[i])
	}
	return acc
}

func main() {
	flag.Parse()
	if *cpuprofile != "" {
		f, err := os.Create(*cpuprofile)
		if err != nil {
			log.Fatal(err)
		}
		pprof.StartCPUProfile(f)
		defer pprof.StopCPUProfile()
	}
	
	input := os.Args[1]
	output := os.Args[2]
	inputF, errIn := os.Open(input)
	outputF, errOu := os.OpenFile(output, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0644)
	check(errIn)
	check(errOu)

	scanner := bufio.NewScanner(inputF)
	scanner.Scan()
	subcadeia, errsb := strconv.Atoi(scanner.Text())
	check(errsb)

	scanner.Scan()
	cadeia := scanner.Text()

	scanner.Scan()
	n, errn := strconv.Atoi(scanner.Text())
	check(errn)
	doencas := make([]Doenca, n)

	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		palavras := strings.Split(scanner.Text(), " ")
		doencas[i].codigo = palavras[0]
		genes, errGene := strconv.Atoi(palavras[1])
		check(errGene)
		doencas[i].genes = make([]string, genes)
		for j := 0; j < genes; j++ {
			doencas[i].genes[j] = palavras[j+2]
		}
	}
	acc := achaCompat(doencas, n, subcadeia, cadeia)
	for i := 100; i >= 0; i-- {
		tam := len(acc[i])
		if tam > 0 {
			for j := 0; j < tam; j++ {
				s := fmt.Sprintf("%s->%d%%\n", acc[i][j].codigo, acc[i][j].probabilidade)
				_, err := outputF.WriteString(s)
				check(err)
			}
		}
	}
	inputF.Close()
	outputF.Close()
}
