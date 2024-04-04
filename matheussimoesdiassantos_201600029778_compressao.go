package compressao

import (
	"bufio"
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

func mochila(pacotes []Pacote, disponiveis []int, veiculo Veiculo) {

	values := make([][]float32, len(pacotes)+1)
	for i := range values {
		values[i] = make([]float32, veiculo.peso+1)
	}

	volumes := make([][]int, len(pacotes)+1)
	for i := range values {
		volumes[i] = make([]int, veiculo.peso+1)
	}

	for i := 0; i <= len(pacotes); i++ {
		for c := 0; c <= veiculo.peso; c++ {

			if i == 0 || c == 0 {
				values[i][c] = 0
				volumes[i][c] = 0
				continue
			} else if pacotes[i-1].peso <= c {
				if pacotes[i-1].valor+values[i-1][c-pacotes[i-1].peso] > values[i-1][c] &&
					pacotes[i-1].volume+volumes[i-1][c-pacotes[i-1].peso] <= veiculo.volume &&
					disponiveis[i-1] == 0 {
					values[i][c] = pacotes[i-1].valor + values[i-1][c-pacotes[i-1].peso]
					volumes[i][c] = pacotes[i-1].volume + volumes[i-1][c-pacotes[i-1].peso]
				} else {
					values[i][c] = values[i][c-1]
					volumes[i][c] = volumes[i][c-1]
				}
			} else {
				values[i][c] = values[i-1][c]
				volumes[i][c] = volumes[i-1][c]
			}
		}
	}

	n := len(pacotes)
	c := veiculo.peso

	for n > 0 {
		if n-1 <= 0 {
			break
		}
		if values[n-1][c] != values[n-2][c] {
			disponiveis[n-1] = 1
			veiculo.pacotes = append(veiculo.pacotes, pacotes[n-1])
			veiculo.num_pacotes++
			c -= pacotes[n-1].peso
		}
		n--
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
	mochila(pacotes, disponiveis, veiculos[0])
	for i := 0; i < len(disponiveis); i++ {
		println(disponiveis[i])
	}

	inputF.Close()
	outputF.Close()
}
