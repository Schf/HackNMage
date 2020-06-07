library mapa;
import 'dart:ui';
import 'package:flame/text_config.dart';

class Character{

  TextConfig textConfig;
  String char;
  
  Character({this.char, this.textConfig});

  modifyChar(String char){
    if(this.char != char){
      this.char = char;
      this.textConfig = new TextConfig(color : _whatColorIsThatChar(char));
    }
  }

  _whatColorIsThatChar(String char){
    //Aqui vai ter um tipo de request pra achar a cor, caso tenham 7 tipos de caracteres, vamos fazer um request a um banco de dados local para deixar mais organizado
    if(char == 'X')
      return Color(0xfaaaaf00);
    else if(char == '.')
      return Color(0xffff4f00);
  }

}

class Campo{

  Rect square;
  Color color;
  Character character;

  Campo(int i, int j){
    if (i == 0 || /*i == MAXVALUE*/ j == 0|| /*j == MAXVALUE*/ j == 10 || i == 10)
      character = new Character(char: 'X', textConfig: new TextConfig(color: Color(0xf5f5f5f5)));
    else
      character = new Character(char: '.', textConfig: new TextConfig(color: Color(0xf5f5f5f5)));
  }

}

class Map{
  var field;
  int width;
  int height;

  Map({this.width, this.height});

  void initMap(){
    field = List<List<Campo>>.generate(width, (i) => List<Campo>.generate(height, (j)=>Campo(i,j)));
  }

}
