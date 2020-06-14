library map;
import 'dart:ui';
import 'package:flame/components/component.dart';
import 'package:flame/components/mixins/resizable.dart';

// -- TEXT --

import 'package:flame/text_config.dart';
import 'package:flame/position.dart';
import 'package:flutter/material.dart';

// -- TEXT END --

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
    //Aqui vai ter um tipo de request pra achar a cor, caso tenham muitos tipos de caracteres, podemos fazer um request a um banco de dados para deixar mais organizado
    if(char == 'X')
      return Color(0xfaaaaf00);
    else if(char == '.')
      return Color(0xffff4f00);
  }

}

class MapSquare{

  Color color;
  Character character;

  MapSquare(int i, int j, maxI, maxJ){
    if (i == 0 || /*i == MAXVALUE*/ j == 0|| /*j == MAXVALUE*/ j == maxJ || i == maxI){
      int colorValue = 0x404040;
      color = Color(0xff000000 + colorValue);
      character = new Character(char: 'X', textConfig: new TextConfig(color: Color ((0xff000000 + colorValue / 4).floor()), fontSize: 22, fontFamily: 'RobotoMono'));
    }
    else{
      int colorValue = 0x202020;
      color = Color(0xff000000 + colorValue);
      character = new Character(char: '.', textConfig: new TextConfig(color: Color ((0xff404080).floor()), fontSize: 22, fontFamily: 'RobotoMono'));
    }
  }
}

class Map extends Component with Resizable{
  var field;
  int widthSquares;
  int heightSquares;
  bool _initated = false;

  Map({this.widthSquares, this.heightSquares});

  initMap(){
    _initated = true;
    field = List<List<MapSquare>>.generate(heightSquares, (i) => List<MapSquare>.generate(widthSquares, (j)=>MapSquare(i, j, heightSquares-1, widthSquares-1)));
  }


  @override
  void render(Canvas canvas) {
      //if(!_initated)
        initMap();
      
      double b = 13;
      double a = (size.width - 2*b) / widthSquares;

      for (int i = 0; i < heightSquares; ++i)
      {
        for (int j = 0; j < widthSquares; ++j)
        {
          canvas.drawRect(Rect.fromLTWH(a*j + b, a*i + b, a*1.005, a*1.005), Paint()..color = field[i][j].color);
          field[i][j].character.textConfig.render (canvas, field[i][j].character.char, Position (a*(j+0.275) + b, a*i + b));
        }
      }
    }
  
    @override
    void update(double t) {}

}
