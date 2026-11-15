bool cmp(const query &a, const query &b)
{
    int b1 = a.l / bb, b2 = b.l / bb;
    if (b1 != b2)
    {
        return b1 < b2;
    }
    return (b1 & 1) ? (a.r < b.r) : (a.r > b.r);
}
int cur_l = 0, cur_r = -1;
for (auto qry : queries)
{
    // Expand range
    while (cur_l > qry.l)
    {
        cur_l--;
        add(cur_l);
    }
    while (cur_r < qry.r)
    {
        cur_r++;
        add(cur_r);
    }
    // Contract range
    while (cur_l < qry.l)
    {
        remove(cur_l);
        cur_l++;
    }
    while (cur_r > qry.r)
    {
        remove(cur_r);
        cur_r--;
    }

    ans[qry.id] = current_ans;
}
struct node
{
    int id;
    int r, c;
    char ch;
    bool operator<(const node &other) const
    {
        return id < other.id;
    }
};