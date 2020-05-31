import 'dart:ui';
import 'package:flame/game.dart';

class HacknMage extends Game {
  Size screenSize;
  @override
  void render(Canvas canvas) {
      
    Rect bgRect = Rect.fromLTWH(0, 0, screenSize.width, screenSize.height);
    Paint bgPaint = Paint();
    bgPaint.color = Color(0xff000000);
    canvas.drawRect(bgRect, bgPaint);
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