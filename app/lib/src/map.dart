library map;
import 'dart:ui';
import 'package:flame/components/component.dart';
import 'package:flame/components/mixins/resizable.dart';
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

  MapSquare(int i, int j, maxJ, maxI){
    if (i == 0 || /*i == MAXVALUE*/ j == 0|| /*j == MAXVALUE*/ j == maxJ || i == maxI){
      character = new Character(char: 'X', textConfig: new TextConfig(color: Color(0x80808080)));
      color = Color(0x80808080);
    }
    else{
      character = new Character(char: '.', textConfig: new TextConfig(color: Color(0xDCDCDCDC)));
      color = Color(0xDCDCDCDC);
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
    field = List<List<MapSquare>>.generate(heightSquares, (i) => List<MapSquare>.generate(widthSquares, (j)=>MapSquare(i,j, widthSquares-1, heightSquares-1)));
  }


  @override
  void render(Canvas canvas) {
      if(!_initated)
        initMap();
      
      double b = 13;
      double a = (size.width - 2*b) / widthSquares;

      for (int i = 0; i < heightSquares; ++i)
        for (int j = 0; j < widthSquares; ++j)
          canvas.drawRect(Rect.fromLTRB(a*j + b, a*i + b, a*(j+1.07) + b, a*(i+1.07) + b), Paint()..color = field[i][j].color);
    }
  
    @override
    void update(double t) {}

}
