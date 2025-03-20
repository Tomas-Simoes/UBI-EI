// --- Manipulação do DOM na página --- //

let btn = document.getElementById('btn')
let h1  = document.querySelector('h1')
let input = document.querySelector('input')
let child_el = document.querySelectorAll('ul li')

for (let i = 0; i < child_el.length; i++) {
    const element = child_el[i];
    element.addEventListener("click", function() {  removeElement(element) })
}

document.addEventListener("DOMContentLoaded", () => {
    h1.textContent = "Olá mundo!"
})

btn.addEventListener('click', btnHandler)
btn.addEventListener('mouseover', removeElement)

function btnHandler () {
    h1.style = "background-color: red"
    h1.textContent = "Mudei o nome o titulo!"
}

input.addEventListener('keydown', inputHandler)

function inputHandler(event) {
    if(event.key === "Enter") {
        event.preventDefault()
        console.log(input.value)
    }
}

function removeElement (el) {
    el.remove()
}