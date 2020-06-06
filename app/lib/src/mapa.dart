library mapa;
import 'dart:ui';
import 'package:flame/game.dart';
import 'package:flame/text_config.dart';

class Quadrado{

  double get left=>left;
  set left(double left)=>this.left = left;

  double get right=>right;
  set right(double right)=>this.right = right;

  double get top=>top;
  set top(double top)=>this.top = top;

  double get bottom=>bottom;
  set bottom(double bottom)=>this.bottom = bottom;

  Color get color=>color;
  set color(Color color)=>this.color = color;

}

class Caracter{
  
  double get posX=>posX;
  set posX(double posX)=>this.posX = posX;

  double get posY=>posY;
  set posY(double posY)=>this.posY = posY;

  TextConfig get textConfig=>textConfig;
  set textConfig(TextConfig textConfig)=>this.textConfig = textConfig;
}

class Campo {
  Quadrado get quadrado=>quadrado;
  set quadrado(Quadrado quadrado)=>this.quadrado = quadrado;

  Caracter get caracter=>caracter;
  set caracter(Caracter caracter)=>this.caracter = caracter;

}

class Mapa {
  List<List<Campo>> mapa;
  int comprimento;
  int largura;

  Mapa({this.comprimento, this.largura});

  
}