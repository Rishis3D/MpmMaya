#pragma once

using namespace std;
class GridField;
class MpmStatus
{
public:
	enum DataFlag
	{
		DATA_PARTICLE = 1,
		DATA_MATRIX   = (1<<1),
		DATA_GRID	  = (1<<2)
	};
	struct GridData 
	{
		Vector3f m_collisionVelocity;
		float	 m_collisionSdf;
	};
	MpmStatus(){}
	MpmStatus( const deque<Particle>& particles, const vector<Matrix4f>& mat, const GridField* grid );
	~MpmStatus();
	void				draw()const;
	bool				copy( deque<Particle>& particles)const;
	bool				copyMatrices(vector<Matrix4f>& mat);
	bool				copyGrid(GridField* grid )const;

	int					getParticleCount()const;
	void			    getParticlePos(int idx, Vector3f& pos)const;
	void				getParticleVelocity( int idx, Vector3f& vel)const;
	const deque<Particle>& getParticle()const{return m_particles;}
	const vector<Matrix4f>&getMatrix()const{return m_matrices;}
	void				writeStatus(ofstream& file) const;
	void				readStatus(ifstream& file, bool append = false);
	const vector<GridData>&getGridData()const{return m_gridData;}
private:
	deque<Particle>	m_particles;
	vector<Matrix4f>m_matrices;
	vector<GridData>m_gridData;

};

class StatusRecorder
{
public:
	typedef map<int,MpmStatus> StatusMap;
	typedef deque<int>			LruQueue;
	StatusRecorder():m_lruLength(100){}

	void				clear(int startFrame = 0);

	bool				addStatus(int ithFrame, const MpmStatus& status);
	bool				getStatus(int ithFrame, MpmStatus& status);
	const MpmStatus*	getStatusPtr(int ithFrame);
	bool				readStatus(const char* fileName, int ithFrame, bool append);
	bool				writeStatus(const char* fileName, int ithFrame);

private:
	/*
	bool				updateLRU(int frameID, vector<int>& itemToDelete)
	{
		LruQueue::iterator pI = m_lru.find(frameID);
		if (pI != m_lru.end())
		{
			m_lru.erase(pI);
		}
		m_lru.push_front(pI);

		if (m_lru.size() > m_lruLength)
		{
			itemToDelete.clear();
			for (int i = m_lruLength; i < m_lru.size(); ++i)
			{
				itemToDelete.push_back(i);
			}
			m_lru.resize(m_lruLength);
		}
	}

	bool				deleteItems(const vector<int>& ids)
	{
		for (int i = 0; i < ids.size(); ++i)
		{
			int id = ids[i];
			StatusMap::iterator pS = m_statusList.find(id);
			if (pS == m_statusList.end())
			{
				continue;
			}


		}
	}*/

	int					m_lruLength;
	StatusMap			m_statusList;
	LruQueue			m_lru;
};