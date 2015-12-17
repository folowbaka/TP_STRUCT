//On fait attention de ne pas comparer dans la même macro la valeur signed et unsigned... Sinon, ça pose probleme.
//Ou alors, il faut que la valeur signed apparaisse avant la signed...
#define Value(g) (g.type==ULONG ? (g.data.u) : (Value2(g)) )
#define Value2(g) (g.type==DOUBLE ? (g.data.d) : (g.data.l) )




/*generique add(generique g1, generique g2)
{
    generique r;

    if(g1.type == DOUBLE || g2.type == DOUBLE)
    {
        r.type = DOUBLE;
        r.data.d =  Value(g2);
        r.data.d += Value(g1);
    }

    else if(g1.type == LONG || g2.type == LONG)
    {
        r.type = LONG;
        r.data.l = Value(g2);
        r.data.l += Value(g1);
    }

    else
    {
        r.type = ULONG;
        r.data.u = g1.data.u + g2.data.u;
    }

    return r;
}*/















