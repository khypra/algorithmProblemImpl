package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Pacote struct {
	codigo    string
	valor     float32
	peso      int
	volume    int
	idVeiculo int
}

type Veiculo struct {
	placa       string
	peso        int
	volume      int
	pacotes     []Pacote
	num_pacotes int
}

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func maxInt(x, y int) int {
	if x > y {
		return x
	}
	return y
}

func max(x, y float32) float32 {
	if x > y {
		return x
	}
	return y
}

func mochila(pacotes []Pacote, disponiveis []int, veiculos []Veiculo, maxP int, maxV int) {

	values := make([][][][]float32, len(pacotes)+1)
	for i := range values {
		values[i] = make([][][]float32, len(veiculos)+1)
		for j := range values[i] {
			values[i][j] = make([][]float32, maxV+1)
			for k := range values[i][j] {
				values[i][j][k] = make([]float32, maxP+1)
			}
		}
	}

	println(len(pacotes), len(veiculos), maxP, maxV)

	for i := 1; i <= len(pacotes); i++ {
		for k := 1; k <= len(veiculos); k++ {
			for c := 1; c <= maxP; c++ {
				for v := 1; v <= maxV; v++ {
					if pacotes[i-1].peso <= c && pacotes[i-1].volume <= v {
						prox := pacotes[i-1].valor + values[i-1][c-pacotes[i-1].peso][v-pacotes[i-1].volume][k]
						ant := values[i-1][c][v][k]
						values[i][c][v][k] = max(prox, ant)
						continue
					}
					values[i][c][v][k] = values[i-1][c][v][k]
				}
			}
		}
	}

	n := len(pacotes)
	k := len(veiculos)
	c := maxP
	v := maxV
	i := n
	for i >= 1 {
		if values[i][c][v][k] != values[i-1][c][v][k] {
			disponiveis[i-1] += 1
			veiculos[k-1].pacotes = append(veiculos[k-1].pacotes, pacotes[i-1])
			veiculos[k-1].num_pacotes++
			c -= pacotes[i-1].peso
			v -= pacotes[i-1].volume
		}
		if i <= 1 {
			i = n
			c = maxP
			v = maxV
			continue
		}
		i--
	}
}

func main() {

	input := os.Args[1]
	output := os.Args[2]
	inputF, errIn := os.Open(input)
	outputF, errOu := os.Open(output)
	check(errIn)
	check(errOu)

	scanner := bufio.NewScanner(inputF)
	scanner.Scan()
	n, errAtN := strconv.Atoi(scanner.Text())
	check(errAtN)

	var veiculos []Veiculo
	var pacotes []Pacote
	maxP := 0
	maxV := 0
	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}

		var errr error
		var carro *Veiculo = new(Veiculo)
		s := strings.Split(scanner.Text(), " ")

		carro.placa = s[0]
		carro.peso, errr = strconv.Atoi(s[1])
		check(errr)
		carro.volume, errr = strconv.Atoi(s[2])
		check(errr)
		veiculos = append(veiculos, *carro)
		maxP = maxInt(maxP, carro.peso)
		maxV = maxInt(maxV, carro.volume)
	}
	scanner.Scan()
	m, errAtM := strconv.Atoi(scanner.Text())
	check(errAtM)
	for i := 0; i < m; i++ {
		if !scanner.Scan() {
			break
		}
		var errr error
		var temp float64
		var pacote *Pacote = new(Pacote)
		s := strings.Split(scanner.Text(), " ")

		pacote.codigo = s[0]
		temp, errr = strconv.ParseFloat(s[1], 64)
		check(errr)
		pacote.valor = float32(temp)
		pacote.peso, errr = strconv.Atoi(s[2])
		check(errr)
		pacote.volume, errr = strconv.Atoi(s[3])
		check(errr)
		pacotes = append(pacotes, *pacote)
	}

	disponiveis := make([]int, m)

	mochila(pacotes, disponiveis, veiculos, maxP, maxV)
	for i := 0; i < len(veiculos); i++ {
		for j := 0; j < veiculos[i].num_pacotes; j++ {
			fmt.Println("q", i, " :", veiculos[i].pacotes[j].valor)
		}
	}
	inputF.Close()
	outputF.Close()
}
