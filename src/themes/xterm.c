#include "../../include/themes/theme.h"
#include <stdio.h>

// RGB xterm[256];

#define INT_MAX 1000

void mapColor(color *xterm) {
  for (int i = 0; i < 216; i++) {
    int r = (i / 36) % 6;
    int g = (i / 6) % 6;
    int b = i % 6;

    xterm[i + 16].r = r == 0 ? 0 : r * 40 + 55;
    xterm[i + 16].g = g == 0 ? 0 : g * 40 + 55;
    xterm[i + 16].b = b == 0 ? 0 : b * 40 + 55;
  }

  for (int i = 0; i < 24; i++) {
    int v = 8 + i * 10;
    xterm[i + 232].r = v;
    xterm[i + 232].g = v;
    xterm[i + 232].b = v;
  }
}

color hexTo3bit(char *hex) {
  color c;
  int r, g, b;

  if (sscanf(hex + 1, "%2x%2x%2x", &r, &g, &b) != 3) {

    return (color){0};
  }

  c.r = r;
  c.g = g;
  c.b = b;

  return c;
}

int colorDistance(color a, color b) {

  int dr = a.r - b.r;
  int dg = a.g - b.g;
  int db = a.b - b.b;
  return dr * dr + dg * dg + db * db;
}

int hexToXterm(char *hex, color *xterm) {
  if (!xterm) {
    printf("xterm palette is NULL\n");
    return 1;
  }
  color target = hexTo3bit(hex);

  int bestIndex = 0;
  int bestDist = INT_MAX;

  for (int i = 0; i < 256; i++) {
    int dist = colorDistance(target, xterm[i]);
    if (dist < bestDist) {
      bestDist = dist;
      bestIndex = i;
    }
  }

  return bestIndex;
}

int bitToXterm(color bit, color *xterm) {
  color target = bit;
  int bestIndex = 0;
  int bestDist = INT_MAX;

  for (int i = 0; i < 256; i++) {
    int dist = colorDistance(target, xterm[i]);
    if (dist < bestDist) {
      bestDist = dist;
      bestIndex = i;
    }
  }

  return bestIndex;
}
