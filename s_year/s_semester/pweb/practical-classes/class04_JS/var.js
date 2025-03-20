// --- Variaveis --- //

var nome = "simoes";
console.log(nome);

nome = "limoes";
console.log(nome);

let idade = 20;
console.log(idade);

idade = 21;
console.log(idade);

const PI = 3.14;
console.log(PI);

let frase= "Olá Mundo!"
console.log(typeof frase);

let numero = 10;
console.log(typeof numero);

let verdadeiro = true;
console.log(typeof verdadeiro);

let lista = ["banana", "maçã", "laranja"];
console.log(typeof lista);

let pessoa = {
    nome: "Leonardo",
    idade: 20
};
console.log(typeof pessoa);

let nulo = null;
console.log(typeof nulo);

let indefinido;
console.log(typeof indefinido);

//---------------------------------//

let toma = 1
const constante = 2
// constante = 3 -> Uncaught TypeError: invalid assignment to const 'constante'
let array = [1, 2, 3, 'quatro', 'cinco']
console.log(array)

let objeto = {
    propriedade1: "yo",
    propriedade2: "foo"
}
console.log(objeto.propriedade1, objeto.propriedade2)

