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
    bgPaint.color = Color(0xf5f5f5f5);
    Rect.fromLTRB(0, 0, 0, 0);

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