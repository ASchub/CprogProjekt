void forAll(void (Loppa::*funk)(int), int arg){
  for(int i=0; i < loppor.size(); i++)
    (loppor[i]->*funk)(arg);
}

/* for-loopen: */
for(;;){
  int cmd;
  // cmd tilldelas ett av värdena HOPPA,SJUNGA,SNURRA eller BRYT

  switch(cmd){
  case HOPPA:
    forAll(&Loppa::hoppa, 3);
    break;
  case SJUNGA:
    forAll(&Loppa::sjunga, 3);
    break;
  case SNURRA:
    forAll(&Loppa::snurra, 3);
    break;
  case BRYT:
    return 0;
  }
}


