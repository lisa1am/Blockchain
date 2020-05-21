import signature

keys=signature.generatePairKey();
priv=split(keys,1);
pub = signature.split(keys,0);
signature.sign(priv,"5a822196bf1c45b1e74c6d04e4127d0296d64695932f40909bdab3ba8a9b0528");
bool = signature.verify(pub, "5a822196bf1c45b1e74c6d04e4127d0296d64695932f40909bdab3ba8a9b0528", sig);
print(bool);
