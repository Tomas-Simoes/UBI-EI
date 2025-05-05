const { Schema, model } = require('mongoose');

const NotaSchema = new Schema({
  codigo: { type: Number, unique: true, required: true },
  nomeProfessor: String,
  nomeDisciplina: String,
  nota: Number
});
module.exports = model('Nota', NotaSchema);
