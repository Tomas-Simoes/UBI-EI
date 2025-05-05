const express = require("express");
const app = express()
const path = require('path')
const fs = require('fs')
const NotasModel = require('../models/notas')

/*
const FILE_NOTAS = path.join(__dirname, '../shared/ficheiro_notas.txt')

function readFile() {
  try {
    return JSON.parse(fs.readFileSync(FILE_NOTAS, 'utf8'));
  } catch (erro) {
    console.error('Erro ao ler o ficheiro:', erro);
    return [];
  }
}

function saveToFile(notas) {
  try {
    fs.writeFileSync(FILE_NOTAS, JSON.stringify(notas, null, 2), 'utf8');
    return true;
  } catch (erro) {
    console.error('Erro ao gravar o ficheiro:', erro);
    return false;
  }
}

let minhas_notas = readFile();
*/


app.get('/notas', async (req, res) => {
    try {
        const notas = await NotasModel.find()
        res.json(notas)
    } catch (err) {
        res.status(500).json({ erro: err.message });
    }
});

app.get("/notas/:codigo", async (req, res) => {
  const codigo = parseInt(req.params.codigo);
  const nota = await NotasModel.findOne({ codigo });   

  if (!nota) return res.status(404).json({ erro: 'Nota não encontrada' });

  res.json(nota);
});

app.post("/notas", async (req, res) => {
    try {
        const novaNota = await NotasModel.create(req.body);   
        res.status(201).json(novaNota);
      } catch (err) {
        res.status(400).json({ erro: err.message });
      }
});

app.put("/notas/:codigo", async (req, res) => {
    const codigo = parseInt(req.params.codigo);
    try {
      const notaAtualizada = await NotasModel.findOneAndUpdate(
        { codigo },
        { $set: req.body },
        { new: true }
      );                                              
      if (!notaAtualizada) return res.status(404).json({ erro: 'Nota não existe' });
      res.json(notaAtualizada);
    } catch (err) {
      res.status(400).json({ erro: err.message });
    }
});

app.delete("/notas/:codigo", async (req, res) => {
const codigo = parseInt(req.params.codigo);
  try {
    const resultado = await NotasModel.findOneAndDelete({ codigo }); 
    
    if (!resultado) return res.status(404).json({ erro: 'Nota não encontrada' });
    
    res.json({ mensagem: 'Nota removida', nota: resultado });
  } catch (err) {
    res.status(500).json({ erro: err.message });
  }
});

module.exports = app