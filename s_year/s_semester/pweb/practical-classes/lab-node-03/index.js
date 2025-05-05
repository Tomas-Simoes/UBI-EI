const express = require('express');
const path = require('path')
const mongoose = require('mongoose')

connectDb()

const app = express();
const port = 3000;

app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

const notasController = require('./controllers/notas');

app.use('/', notasController);

app.listen(port, () => {
  console.log(`Servidor rodando na porta ${port}`);
});

async function connectDb() {
    try {
      await mongoose.connect("mongodb+srv://tomas20simoes:2EmJGfg9NywYsCEq@lab-node-03.xkde5ma.mongodb.net/?retryWrites=true&w=majority&appName=lab-node-03");
      console.log('MongoDB ligado com sucesso');
    } catch (err) {
      console.error('Erro ao ligar ao MongoDB:', err);
      process.exit(1);
    }
  }