struct trie {
	array<trie *, 3> go;
	trie *fail;
	int output, idx;
	trie() {
		fill(go.begin(), go.end(), nullptr);
		fail = nullptr;
		output = idx = 0;
	}
	~trie() {
		for (auto &x : go)
			delete x;
	}
	void insert(const string &input, int i) {
		if (i == input.size())
			output++;
		else {
			const int x = input[i] - 'A';
			if (!go[x])
				go[x] = new trie();
			go[x]->insert(input, i+1);
		}
	}
};
queue<trie*> q; // make fail links; requires root->insert before
root->fail = root;
q.push(root);
while (!q.empty()) {
    trie *curr = q.front();
    q.pop();
    for (int i=0; i<26; ++i) {
        trie *next = curr->go[i];
        if (!next)
            continue;
        if (curr == root)
            next->fail = root;
        else {
            trie *dest = curr->fail;
            while (dest != root && !dest->go[i])
                dest = dest->fail;
            if (dest->go[i])
                dest = dest->go[i];
            next->fail = dest;
        }
        if (next->fail->output)
            next->output = true;
        q.push(next);
    }
}
trie *curr = root; // start query
bool found = false;
for (char c : s) {
    c -= 'a';
    while (curr != root && !curr->go[c])
        curr = curr->fail;
    if (curr->go[c])
        curr = curr->go[c];
    if (curr->output) {
        found = true;
        break;
    }
}