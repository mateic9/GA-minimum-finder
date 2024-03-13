Programul implementeaza operatorii de selectie, incrucisare si mutatie specifici unor algoritmi genetici pentru a afla punctele de minim ale unor functii(Rastrigin,Schweffel,DeJong,Michalewicz) pe un anumit interval.Pentru selectia indivizilor din generatiile viitoare, am folosit tehnici precum Wheel of Fortune si elitism, iar functia de fitness folosita este f(x)=1/(fct(individ)+30). 
 <br />
Functia pentru care dorim sa determinam minimul este data ca parametru in mainFunction() din interiorul functiei main().  <br />
Parametrizarea algoritmului se face prin intermediul macrourilor:  <br />
  -nrOfDimension : specifica numarul de dimensiuni ale planului in care efectuam cautarea  <br />
  -mutationRate : specifica frecventa aplicarii operatorului de mutatie  <br />
  -crossRate : specifica frecventa aplicarii operatorului de incrucisare   <br />
  -Untouchable : specifica numarul  de indivizi din generatia curenta care in urma procesului de elitism vor ajunge in generatia urmatoare  <br />
  -putereAmplificare : este folosit in functia fitness(ex. f(x)=pow(1 / (fct(individ)+30),putereAmplificare) )   <br />
  -capatMicInterval si capatMateInterval specifica extremitatile intervalului de valori pentru componenta de pe o dimensiune

