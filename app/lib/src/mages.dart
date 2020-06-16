import 'dart:ui';

import 'package:flame/components/component.dart';
import 'package:flame/components/mixins/resizable.dart';
import 'package:flame/position.dart';

// -- TEXT --

import 'package:flame/text_config.dart';

class FireMage extends Component with Resizable{
  
  String char = 'f';
  TextConfig frame1 = new TextConfig(color: Color.fromRGBO(246,211,25, 1.0) );
  TextConfig frame2 = new TextConfig(color: Color.fromRGBO(246,101,25, 1.0) );
  TextConfig frame3 = new TextConfig(color: Color.fromRGBO(246,25,59,  1.0) );
  int trade = 0;

  @override
  void render(Canvas canvas) {
    var frame = () {
      if(trade == 0){
        ++trade;
        return frame1;
      }
      else if(trade == 1){
        ++trade;
        return frame2;
      }
      else{
        trade = 0;
        return frame3;
      }
    };
    double b = 13;
    double a = (size.width - 2*b) / 11;
    frame.call().render(canvas, char, Position (a*(3+0.275) + b, a*2 + b));
  }
  
  @override
  void update(double t) {}

}