import 'dart:ui';
import 'package:flame/game.dart';
import 'package:flame/text_config.dart';
import 'package:flame/position.dart';

class HacknMage extends Game {
  Size screenSize;
  @override
  void render(Canvas canvas) {
      
    Rect bgRect = Rect.fromLTWH(0, 0, screenSize.width, screenSize.height);
    Paint bgPaint = Paint();
    bgPaint.color = Color(0xff000000);
    canvas.drawRect(bgRect, bgPaint);
    bgPaint.color = Color(0xf5f5f5f5);
    Rect novo = Rect.fromLTRB(0, 0, 30, 30);
    canvas.drawRect(novo, bgPaint);
    const TextConfig config = TextConfig(fontSize: 20.0, fontFamily: 'Awesome Font');
    config.render(canvas, "Flame is awesome", Position(5, 5));

  }
  
  @override
  void update(double t) {
    // TODO: implement update
  }

  @override
  void resize(Size size){
    screenSize = size;
    super.resize(size);
  }  

}