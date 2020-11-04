#include <math.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <sstream>

using namespace std;
const float PI = 3.14159265;

// geometrische Paramter
float cristal_width = 1.6358204297888304;
float cristal_length = 1.6358204297888304;
float volume = cristal_width * cristal_width * cristal_length;

// phyiskalische Paramter
float refract_index = 2.4;
float alphaG = asin(1 / refract_index);
float verstaerkung = 1.4076026017668022;

// numerische Paramter
int res = 30;
float dx = cristal_width / res;
float dy = cristal_width / res;
float dz = cristal_length / res;
float dphi = 2 * PI / res;
float dtheta = PI / res;
bool tests = true;

// Weglänge i.Abh. von x,y,z, theta. phi
float len(float x, float y, float z, float theta, float phi) {
  // Distanz zur Mantelfläche
  float distMant;

  // Grenzwinkel für vorne, rechts, hinten und links
  float phiA = atan((cristal_width - y) / (cristal_width - x));
  float phiB = atan(x / (cristal_width - y)) + PI / 2;
  float phiC = atan(y / x) + PI;
  float phiD = 2 * PI - atan(y / (cristal_width - x));
  if (phi >= phiD || phi < phiA) {
    distMant = abs((cristal_width - x) / (sin(theta) * cos(phi)));
  } else if (phi < phiB) {
    distMant = abs((cristal_width - y) / (sin(theta) * sin(phi)));
  } else if (phi < phiC) {
    distMant = abs(x / (sin(theta) * cos(phi)));
  } else {
    distMant = abs(y / (sin(theta) * sin(phi)));
  }

  // Mantelfläche oder Deckfläche i. Abh. von theta
  if (theta < alphaG) {
    float g_oben = (cristal_length - z) / cos(theta);
    return min(distMant, g_oben);
  }
  if (theta > PI - alphaG) {
    float g_unten = -z / cos(theta);
    return min(distMant, g_unten);
  }
  return distMant;
}

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    cout << "usage: " << argv[0] << " number of Stützstellen" << endl;
    return -1;
  }
  stringstream ss;
  ss << argv[1];
  ss >> res;
  float dx = cristal_width / res;
  float dy = cristal_width / res;
  float dz = cristal_length / res;
  float dphi = 2 * PI / res;
  float dtheta = PI / res;
  bool tests = true;

  float eps = 1e-3;
  random_device device;
  mt19937 generator(device());
  uniform_real_distribution<float> dis(0, 1.0);

  float Gain = 0;
  float dxyzPhiTheta = dx * dy * dz * dphi * dtheta / 4 / PI;

  if (tests) {
    cout << len(1.1122256115771822, 0.5764649159972031, 1.2861825133965261,
                0.844848403165887, 3.5039244456069807)
         << " vs 1.5904537733235915" << endl;
    cout << len(0.4311388552573979, 1.3203020322026073, 0.23954333239486553,
                1.2355078716713435, 2.17094364328996)
         << " vs 0.4048748406636025" << endl;
    cout << len(1.0898329874149761, 1.38651401615737, 0.6786205756169365,
                0.41567276167769407, 4.475439844193751)
         << " vs 1.046297457867359" << endl;
    cout << len(1.4160180062786953, 1.0221510720252873, 0.5432612370216389,
                0.3814245656738259, 3.8807949899076633)
         << " vs 1.1771550992105257" << endl;
    cout << len(0.4140748976338365, 0.8742786068091878, 0.4011852121349583,
                0.7291969910138519, 2.9527594336857685)
         << " vs 0.6327285916911016" << endl;
    cout << len(0.34443604633526403, 0.9115062964829308, 1.0245195815705308,
                1.0500372623276775, 4.373792447434115)
         << " vs 1.114052162563139" << endl;
    cout << len(1.4344434001480255, 0.08119006635370332, 0.8501320066513149,
                0.2502560045036482, 2.7335976464338128)
         << " vs 0.810950292363331" << endl;
    cout << len(1.0474536305982896, 0.8921445622717136, 0.22607760111663366,
                1.8368725449931882, 3.8915687301077395)
         << " vs 1.3565952125184975" << endl;
    cout << len(0.9595416599107074, 0.2909909286819207, 0.621436355040488,
                2.169750564674727, 3.4735085202715714)
         << " vs 1.0812203517616326" << endl;
    cout << len(0.7375166875548543, 0.6120524255753914, 0.5919832873009587,
                1.6254016977100318, 4.6192778169342)
         << " vs 0.6156327981116153" << endl;
  }
  cout << "Res: " << res << endl;
  for (int i = 0; i < res; i++) {
    float zwischensumme = 0;
    for (int j = 0; j < 100; j++) {
      float x = eps + dis(generator) * (cristal_width - 2 * eps);
      float y = eps + dis(generator) * (cristal_width - 2 * eps);
      float z = eps + dis(generator) * (cristal_length - 2 * eps);
      float phi = 2 * PI * dis(generator);
      float theta = acos(2 * dis(generator) - 1);
      zwischensumme += exp(verstaerkung * len(x, y, z, theta, phi));
    }
    Gain += zwischensumme / 100.0;
  }
  Gain *= 1.0 / res;
  // Gain *= dxyzPhiTheta;
  cout << Gain << endl;
  cout << volume << endl;
  return 0;
}
