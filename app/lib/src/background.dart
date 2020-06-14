library background;

import 'dart:ui';

import 'package:flame/components/component.dart';
import 'package:flame/components/mixins/resizable.dart';

class Background extends Component with Resizable{
  @override
  void render(Canvas canvas) {   

      Rect bgRect = Rect.fromLTWH(0, 0, size.width, size.height); //Red Margin
      Paint bgPaint = Paint();
      bgPaint.color = Color(0xffa00000);
      canvas.drawRect(bgRect, bgPaint);
      bgRect = Rect.fromLTRB(3, 3, size.width - 3, size.height - 3); //Black Background
      bgPaint.color = Color(0xff000000);
      canvas.drawRect(bgRect, bgPaint);
    }
  
    @override
    void update(double t) {}

}