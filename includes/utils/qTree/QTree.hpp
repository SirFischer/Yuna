/*
 * File: QTree.hpp
 * Project: Extermination
 * File Created: Sunday, 31st October 2021 7:15:53 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 7th May 2022 7:42:52 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */

#pragma once
#include <vector>
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>

//This can be overwritten by creating the constant before including this file.
#ifndef MAX_QUADTREE_NODES
	#define MAX_QUADTREE_NODES 9
#endif

namespace Yuna
{
	namespace Utils
	{
		template <typename T>
		struct NodeData
		{
			sf::FloatRect	mRect;
			T				mData;

			NodeData(T pData, sf::FloatRect pRect)
			{
				mRect = pRect;
				mData = pData;
			}
		};

		template <typename T>
		class QTree
		{
		private:
			std::vector<NodeData<T>>	mData;
			sf::FloatRect				mRect;

			std::unique_ptr<QTree<T>>	mNorthWest;
			std::unique_ptr<QTree<T>>	mSouthWest;
			std::unique_ptr<QTree<T>>	mSouthEast;
			std::unique_ptr<QTree<T>>	mNorthEast;

		public:
			QTree(sf::FloatRect	pRect);
			~QTree();

			sf::FloatRect							GetGlobalBounds(){return (mRect);}
			bool									Insert(T pData, sf::FloatRect pRect);
			bool									Insert(NodeData<T> pNode);
			bool									DeleteAt(const sf::FloatRect &pWithin, const sf::Vector2f &pPos);
			void									Subdivide();
			void									Render(sf::RenderWindow *pWindow, int pLevel);
			std::list<std::vector<NodeData<T>> *>	Query(sf::FloatRect pRect);
			void									ForEach(sf::FloatRect mWithin, std::function<void(const T &pData)> pFunction);
		};

		template <typename T>
		QTree<T>::QTree(sf::FloatRect	pRect)
		{
			mRect = pRect;
		}

		template <typename T>
		QTree<T>::~QTree()
		{
		}

		template <typename T>
		bool		QTree<T>::Insert(T pData, sf::FloatRect pRect)
		{
			NodeData<T> node(pData, pRect);
			return (Insert(node));
		}

		template <typename T>
		bool		QTree<T>::Insert(NodeData<T> pNode)
		{
			if (!pNode.mRect.intersects(mRect))
				return (false);
			if (mData.size() < MAX_QUADTREE_NODES && !mNorthWest)
			{
				mData.push_back(pNode);
				return (true);
			}
			if (!mNorthWest)
				Subdivide();

			if (mNorthWest->Insert(pNode)) return (true);
			if (mNorthEast->Insert(pNode)) return (true);
			if (mSouthEast->Insert(pNode)) return (true);
			if (mSouthWest->Insert(pNode)) return (true);

			return (false);
		}

		template <typename T>
		bool		QTree<T>::DeleteAt(const sf::FloatRect &pWithin, const sf::Vector2f &pPos)
		{
			if (!mRect.intersects(pWithin))
				return (false);

			if (mNorthWest)
			{
				if (mNorthWest->DeleteAt(pWithin, pPos)) return (true);
				if (mNorthEast->DeleteAt(pWithin, pPos)) return (true);
				if (mSouthWest->DeleteAt(pWithin, pPos)) return (true);
				if (mSouthEast->DeleteAt(pWithin, pPos)) return (true);
				return (false);
			}
			const auto size = mData.size();
			auto it = std::remove_if(mData.begin(), mData.end(), [pPos](const NodeData<T> &data){
				return (data.mRect.contains(pPos));
			});
			mData.erase(it, mData.end());
			return (size != mData.size());
		}


		template <typename T>
		void		QTree<T>::Subdivide()
		{
			mNorthEast = std::make_unique<QTree<T>>(sf::FloatRect(mRect.left + (mRect.width / 2.f), mRect.top, mRect.width / 2.f, mRect.height / 2.f));
			mNorthWest = std::make_unique<QTree<T>>(sf::FloatRect(mRect.left, mRect.top, mRect.width / 2.f, mRect.height / 2.f));
			mSouthWest = std::make_unique<QTree<T>>(sf::FloatRect(mRect.left, mRect.top + (mRect.height / 2.f), mRect.width / 2.f, mRect.height / 2.f));
			mSouthEast = std::make_unique<QTree<T>>(sf::FloatRect(mRect.left + (mRect.width / 2.f), mRect.top + (mRect.height / 2.f), mRect.width / 2.f, mRect.height / 2.f));
			for (auto &i : mData)
				Insert(i);
			mData.clear();
		}


		template <typename T>
		std::list<std::vector<NodeData<T>>*> QTree<T>::Query(sf::FloatRect pRect)
		{
			std::list<std::vector<NodeData<T>>*>	list;
			if (!mRect.intersects(pRect))
				return (list);
			list.push_front(&mData);
			if (mNorthWest)
			{
				list.merge(mNorthWest->Query(pRect));
				list.merge(mNorthEast->Query(pRect));
				list.merge(mSouthWest->Query(pRect));
				list.merge(mSouthEast->Query(pRect));
			}
			return (list);
		}

		template <typename T>
		void	QTree<T>::Render(sf::RenderWindow *pWindow, int pLevel)
		{
			if (!pLevel)
				return ;
			sf::VertexArray quad(sf::LineStrip, 4);
			quad[0].position = sf::Vector2f(mRect.left, mRect.top);
			quad[1].position = sf::Vector2f(mRect.left + mRect.width, mRect.top);
			quad[2].position = sf::Vector2f(mRect.left + mRect.width, mRect.top + mRect.height);
			quad[3].position = sf::Vector2f(mRect.left, mRect.top + mRect.height);

			quad[0].color = sf::Color::Red;
			quad[1].color = sf::Color::Red;
			quad[2].color = sf::Color::Red;
			quad[3].color = sf::Color::Red;

			pWindow->draw(quad);
			if (mNorthWest)
			{
				mNorthWest->Render(pWindow, pLevel - 1);
				mNorthEast->Render(pWindow, pLevel - 1);
				mSouthEast->Render(pWindow, pLevel - 1);
				mSouthWest->Render(pWindow, pLevel - 1);
			}
		}

		template <typename T>
		void	QTree<T>::ForEach(sf::FloatRect mWithin, std::function<void(const T &pData)> pFunction)
		{
			if (!mRect.intersects(mWithin))
				return ;
			if (!mNorthWest)
			{
				for (auto &data : mData)
					pFunction(data.mData);
			}
			else
			{
				mNorthWest->ForEach(mWithin, pFunction);
				mNorthEast->ForEach(mWithin, pFunction);
				mSouthWest->ForEach(mWithin, pFunction);
				mSouthEast->ForEach(mWithin, pFunction);
			}
		}



	} // namespace Utils
} // namespace Yuna
