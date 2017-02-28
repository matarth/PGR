Semestrální práce pro předmět "Programování grafiky". Program je zkompilovaný pro Windows a k běhu potřebuje knihovny: 
* freeglut.gll
* Assimp32.dll
* DevIL.dll

Program funguje jako primitivní engine pro vkládání objektů do scény a animování objektů. Je napsán v OpenGL s pomocí knihovny Glut, která se stará o uživatelské vstupy a o zobrazování. Osvětlování je implementováno pomocí Phongova osvětlovacího modelu.

**Popis scény:**
Každý model se dá vybrat kliknutím, a následně s ním otáčet myší, nebo s ním cestovat po scéně pomocí klávesnice.
**Ovládání**

* Kliknutím na skybox nebo terén se jako aktivní model zvolí kamera uživatele.
* Kliknutím na libovolný objekt tento objekt zvolíme jako aktivní.
* L: vypne všechny animace objektu.
* F: zapne otáčení pomocí myši.(Freecamera)
* G: vypne otáčení pomocí myši.
* W/S/A/D: pohybo objektem po scéně.
* 3: animace Pitch. Začne otáčet objektem po jeho ose X.
* 1: Kamera začne sledovat letadlo.
* 9: Kamera se začne pohybovat po křivce.
* 4: Na letadle se začne měnit textura.
* 7/8: Statické pohledy

![screen1](https://github.com/matarth/pgr/blob/master/1.png?raw=true)
![screen2](https://github.com/matarth/pgr/blob/master/2.png?raw=true)
![screen3](https://github.com/matarth/pgr/blob/master/3.png?raw=true)

