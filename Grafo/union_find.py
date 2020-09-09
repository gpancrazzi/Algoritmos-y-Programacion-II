class UnionFind(Object):
    def __init__(self, n):
        self.groups = list(range(n))

    def find(self, v):
        """Verifica a que conjunto pertene el nodo."""
        if self.groups[v] == v: return v
        real_group = self.find(self.groups[v])
        self.groups[v] = real_group
        return real_group

    def union(self, u, v):
        """Une un nodo a un conjunto."""
        new_group = self.find(u)
        other = self.find(v)
        self.groups[other] = new_group